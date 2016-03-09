#include "GameServer.h"


//
// 客户端链接回调
//
void CGameServer::OnConnect(CIOContext *pIOContext, SOCKET acceptSocket)
{
	((CPlayer *)pIOContext)->SetFlags(FlagsCode::Code::PLAYER_FLAGS_NONE);
	CIOCPServer::OnConnect(pIOContext, acceptSocket);
}

//
// 客户端断链回调
//
void CGameServer::OnDisconnect(CIOContext *pIOContext)
{
	OnExitGame((CPlayer *)pIOContext, 0);
	Logout((CPlayer *)pIOContext);

	CIOCPServer::OnDisconnect(pIOContext);
}

//
// 更新发送消息
//
void CGameServer::OnUpdateSend(void)
{
	if (CPlayer *pPlayer = (CPlayer *)m_pActiveContext) {
		do {
			if (pPlayer->IsAlive()) {
				pPlayer->sendBuffer.Lock();
				{
					pPlayer->OnSendNext(NULL, 0, 0);
				}
				pPlayer->sendBuffer.Unlock();
			}
		} while (pPlayer = (CPlayer *)pPlayer->pNextActive);
	}
}

//
// 更新接收消息
//
void CGameServer::OnUpdateRecv(DWORD dwDeltaTime)
{
	CPlayer *pPlayer = (CPlayer *)m_pActiveContext;

	while (pPlayer) {
		CPlayer *pNextPlayer = (CPlayer *)pPlayer->pNextActive;

		if (pPlayer->IsAlive()) {
			pPlayer->recvBuffer.Lock();
			{
				pPlayer->dwHeartTime += dwDeltaTime;

				while (TRUE) {
					WORD msg = 0;
					WORD fullSize = *(WORD *)pPlayer->recvBuffer.GetPopPointer();
					WORD bodySize = fullSize - sizeof(msg);

					if (pPlayer->recvBuffer.GetActiveBufferSize() < sizeof(fullSize) + fullSize) break;
					if (pPlayer->recvBuffer.PopData((BYTE *)&fullSize, sizeof(fullSize)) == FALSE) break;
					if (pPlayer->recvBuffer.PopData((BYTE *)&msg, sizeof(msg)) == FALSE)  break;

					m_dwRecvDataSize += sizeof(fullSize) + fullSize;

					switch (msg) {
					case Client::REQUEST_MSG::HEART:
						OnHeart(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::FLAGS:
						OnFlags(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::LOGIN:
						OnLogin(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::CREATE_GAME:
						OnCreateGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::DESTROY_GAME:
						OnDestroyGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::ENTER_GAME:
						OnEnterGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::EXIT_GAME:
						OnExitGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::SEND_TO_PLAYER:
						OnSendToPlayer(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::REQUEST_MSG::SEND_TO_PLAYER_ALL:
						OnSendToPlayerAll(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					default:
						OnUpdateGameMessage(pPlayer, msg);
						OnHeartReset(pPlayer);
						break;
					}
				}
			}
			pPlayer->recvBuffer.Unlock();
		}

		if (pPlayer->dwHeartTime > (DWORD)(1000 * m_timeOut)) {
			WriteLog("%s: Heart TimeOut\n", pPlayer->ip);
			ReleaseIOContext(pPlayer, FALSE);
		}

		pPlayer = pNextPlayer;
	}
}

//
// 更新游戏消息
//
void CGameServer::OnUpdateGameMessage(CPlayer *pPlayer, WORD msg)
{

}

//
// 更新游戏逻辑
//
void CGameServer::OnUpdateGameLogic(float deltaTime)
{

}

//
// 重置心跳
//
void CGameServer::OnHeartReset(CPlayer *pPlayer)
{
	pPlayer->dwHeartTime = 0;
}

//
// 心跳
//
void CGameServer::OnHeart(CPlayer *pPlayer, WORD size)
{
	::Client::Heart requestHeart;
	::Server::Heart responseHeart;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestHeart, size) == FALSE) {
		return;
	}

	//
	// 2. 心跳
	//
	responseHeart.set_timestamp(requestHeart.timestamp());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseHeart, ::Server::RESPONSE_MSG::HEART);

	//
	// 4. 发送玩家
	//
	SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 标识
//
void CGameServer::OnFlags(CPlayer *pPlayer, WORD size)
{
	::Client::Flags requestFlags;
	::Server::Flags responseFlags;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestFlags, size) == FALSE) {
		return;
	}

	//
	// 2. 标识
	//
	responseFlags.set_flags(pPlayer->GetFlags());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseFlags, ::Server::RESPONSE_MSG::FLAGS);

	//
	// 4. 发送玩家
	//
	SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 登陆
//
void CGameServer::OnLogin(CPlayer *pPlayer, WORD size)
{
	::Client::Login requestLogin;
	::Server::Login responseLogin;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestLogin, size) == FALSE) {
		return;
	}

	//
	// 2. 玩家登陆
	//
	ErrorCode::Code err = ErrorCode::Code::ERR_NONE;

	if (requestLogin.version() != VersionCode::Code::VERSION) {
		err = ErrorCode::Code::ERR_VERSION_INVALID; goto ERR;
	}

	if (pPlayer->GetFlags() != FlagsCode::Code::PLAYER_FLAGS_NONE) {
		err = ErrorCode::Code::ERR_PLAYER_FLAGS_NOT_NONE; goto ERR;
	}

	if (Login(pPlayer, requestLogin.guid()) == FALSE) {
		err = ErrorCode::Code::ERR_PLAYER_INVALID_GUID; goto ERR;
	}

	responseLogin.set_guid(pPlayer->guid);

	goto NEXT;
ERR:
NEXT:
	responseLogin.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseLogin, ::Server::RESPONSE_MSG::LOGIN);

	//
	// 4. 发送玩家
	//
	SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 创建游戏
//
void CGameServer::OnCreateGame(CPlayer *pPlayer, WORD size)
{
	::Client::CreateGame requestCreateGame;
	::Server::CreateGame responseCreateGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestCreateGame, size) == FALSE) {
		return;
	}

	//
	// 2. 创建游戏
	//
	CGame *pGame = NULL;
	ErrorCode::Code err = ErrorCode::Code::ERR_NONE;

	if (pPlayer->pGame != NULL) {
		err = ErrorCode::Code::ERR_PLAYER_FLAGS_INGAME; goto ERR;
	}

	if (pPlayer->GetFlags() != FlagsCode::Code::PLAYER_FLAGS_LOGIN) {
		err = ErrorCode::Code::ERR_PLAYER_FLAGS_NOT_LOGIN; goto ERR;
	}

	pGame = GetNextGame();

	if (pGame == NULL) {
		err = ErrorCode::Code::ERR_SERVER_FULL; goto ERR;
	}

	pGame->SetGame(requestCreateGame.password().c_str(), requestCreateGame.mode(), requestCreateGame.map(), requestCreateGame.maxplayers());
	pGame->AddPlayer(pPlayer, requestCreateGame.password().c_str(), TRUE);

	responseCreateGame.set_gameid(pGame->id);

	goto NEXT;
ERR:
NEXT:
	responseCreateGame.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseCreateGame, ::Server::RESPONSE_MSG::CREATE_GAME);

	//
	// 4. 发送玩家
	//
	SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 销毁游戏
//
void CGameServer::OnDestroyGame(CPlayer *pPlayer, WORD size)
{
	::Client::DestroyGame requestDestroyGame;
	::Server::DestroyGame responseDestroyGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestDestroyGame, size) == FALSE) {
		return;
	}

	//
	// 2. 销毁检查
	//
	ErrorCode::Code err = pPlayer->pGame ? ErrorCode::Code::ERR_NONE : ErrorCode::Code::ERR_PLAYER_FLAGS_NOT_INGAME;
	responseDestroyGame.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseDestroyGame, ::Server::RESPONSE_MSG::DESTROY_GAME);

	//
	// 4. 发送玩家
	//
	if (err == ErrorCode::Code::ERR_NONE) {
		SendToPlayerAll(pPlayer->pGame, NULL, buffer, writeBuffer.GetActiveBufferSize());
	}
	else {
		SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
	}

	//
	// 5. 销毁游戏
	//
	if (err == ErrorCode::Code::ERR_NONE) {
		ReleaseGame(pPlayer->pGame);
	}
}

//
// 进入游戏
//
void CGameServer::OnEnterGame(CPlayer *pPlayer, WORD size)
{
	::Client::EnterGame requestEnterGame;
	::Server::EnterGame responseEnterGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestEnterGame, size) == FALSE) {
		return;
	}

	//
	// 2. 进入游戏
	//
	ErrorCode::Code err = ErrorCode::Code::ERR_NONE;

	if (pPlayer->pGame != NULL) {
		err = ErrorCode::Code::ERR_PLAYER_FLAGS_INGAME; goto ERR;
	}

	if (pPlayer->GetFlags() != FlagsCode::Code::PLAYER_FLAGS_LOGIN) {
		err = ErrorCode::Code::ERR_PLAYER_FLAGS_NOT_LOGIN; goto ERR;
	}

	if (requestEnterGame.gameid() < 0 || requestEnterGame.gameid() >= (DWORD)m_maxGames) {
		err = ErrorCode::Code::ERR_GAME_INVALID_ID; goto ERR;
	}

	err = (ErrorCode::Code)m_games[requestEnterGame.gameid()]->AddPlayer(pPlayer, requestEnterGame.password().c_str(), FALSE);
	if (err != ErrorCode::Code::ERR_NONE) goto ERR;

	responseEnterGame.set_gameid(pPlayer->pGame->id);
	responseEnterGame.set_guid(pPlayer->guid);

	goto NEXT;
ERR:
NEXT:
	responseEnterGame.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseEnterGame, ::Server::RESPONSE_MSG::ENTER_GAME);

	//
	// 4. 发送玩家
	//
	if (err == ErrorCode::Code::ERR_NONE) {
		SendToPlayerAll(pPlayer->pGame, NULL, buffer, writeBuffer.GetActiveBufferSize());
	}
	else {
		SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
	}
}

//
// 退出游戏
//
void CGameServer::OnExitGame(CPlayer *pPlayer, WORD size)
{
	::Client::ExitGame requestExitGame;
	::Server::ExitGame responseExitGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestExitGame, size) == FALSE) {
		return;
	}

	//
	// 2. 退出游戏
	//
	ErrorCode::Code err = pPlayer->pGame ? ErrorCode::Code::ERR_NONE : ErrorCode::Code::ERR_PLAYER_FLAGS_NOT_INGAME;
	responseExitGame.set_err(err);
	responseExitGame.set_guid(pPlayer->guid);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseExitGame, ::Server::RESPONSE_MSG::EXIT_GAME);

	//
	// 4. 发送玩家
	//
	if (err == ErrorCode::Code::ERR_NONE) {
		SendToPlayerAll(pPlayer->pGame, NULL, buffer, writeBuffer.GetActiveBufferSize());
	}
	else {
		SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
	}

	//
	// 5. 退出游戏
	//
	if (err == ErrorCode::Code::ERR_NONE) {
		pPlayer->pGame->DelPlayer(pPlayer);
	}
}

//
// 发送指定玩家
//
void CGameServer::OnSendToPlayer(CPlayer *pPlayer, WORD size)
{
	::Client::SendToPlayer requestSendToPlayer;
	::Server::SendToPlayer responseSendToPlayer;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestSendToPlayer, size) == FALSE) {
		return;
	}

	//
	// 2. 查找目标玩家
	//
	CPlayer *pTarget = QueryPlayer(requestSendToPlayer.guid());
	if (pTarget == NULL) return;

	responseSendToPlayer.set_size(requestSendToPlayer.size());
	responseSendToPlayer.set_data(requestSendToPlayer.data().c_str(), requestSendToPlayer.size());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseSendToPlayer, ::Server::RESPONSE_MSG::SEND_TO_PLAYER);

	//
	// 4. 发送目标玩家
	//
	SendToPlayer(pTarget, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 发送所有玩家
//
void CGameServer::OnSendToPlayerAll(CPlayer *pPlayer, WORD size)
{
	::Client::SendToPlayerAll requestSendToPlayerAll;
	::Server::SendToPlayer responseSendToPlayer;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &requestSendToPlayerAll, size) == FALSE) {
		return;
	}

	//
	// 2. 查找目标玩家
	//
	if (pPlayer->pGame == NULL) {
		return;
	}

	responseSendToPlayer.set_size(requestSendToPlayerAll.size());
	responseSendToPlayer.set_data(requestSendToPlayerAll.data().c_str(), requestSendToPlayerAll.size());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseSendToPlayer, ::Server::RESPONSE_MSG::SEND_TO_PLAYER);

	//
	// 4. 发送所有玩家
	//
	SendToPlayerAll(pPlayer->pGame, pPlayer, buffer, writeBuffer.GetActiveBufferSize(), requestSendToPlayerAll.filter());
}
