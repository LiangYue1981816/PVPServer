#include "GameServer.h"


//
// 客户端链接回调
//
void CGameServer::OnConnect(CIOContext *pIOContext, SOCKET acceptSocket)
{
	((CPlayer *)pIOContext)->SetFlags(PLAYER_FLAGS_NONE);
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
					case Client::SERVER_MSG::HEART:
						OnHeart(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::LOGIN:
						OnLogin(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

						/*
					case Client::SERVER_MSG::FLAGS:
						OnFlags(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;
						*/

					case Client::SERVER_MSG::CREATE_GAME:
						OnCreateGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::DESTROY_GAME:
						OnDestroyGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::ENTER_GAME:
						OnEnterGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::EXIT_GAME:
						OnExitGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::MODIFY_GAME_PASSWORD:
						OnModifyGamePassword(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::SEND_TO_PLAYER:
						OnSendToPlayer(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::SEND_TO_PLAYER_ALL:
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
	::Client::Heart clientHeart;
	::Server::Heart serverHeart;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientHeart, size) == FALSE) {
		return;
	}

	//
	// 2. 心跳
	//
	serverHeart.set_timestamp(clientHeart.timestamp());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverHeart, ::Server::SERVER_MSG::HEART);

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
	::Client::Login clientLogin;
	::Server::Login serverLogin;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientLogin, size) == FALSE) {
		return;
	}

	//
	// 2. 玩家登陆
	//
	int err = ERR_NONE;

	if (err == ERR_NONE) err = clientLogin.version() == GAME_SERVER_VERSION ? ERR_NONE : ERR_VERSION_INVALID;
	if (err == ERR_NONE) err = pPlayer->GetFlags() == PLAYER_FLAGS_NONE ? ERR_NONE : ERR_PLAYER_STATE_LOGIN;
	if (err == ERR_NONE) err = Login(pPlayer, clientLogin.guid()) == TRUE ? ERR_NONE : ERR_PLAYER_INVALID_GUID;
	if (err == ERR_NONE) serverLogin.set_guid(clientLogin.guid());

	serverLogin.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverLogin, ::Server::SERVER_MSG::LOGIN);

	//
	// 4. 发送玩家
	//
	SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 设置标识
//
/*
void CGameServer::OnFlags(CPlayer *pPlayer, WORD size)
{
	::Client::Flags clientFlags;
	::Server::Flags serverFlags;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientFlags, size) == FALSE) {
		return;
	}

	//
	// 2. 设置标识
	//
	int err = ERR_NONE;

	if (err == ERR_NONE) err = pPlayer->IsLogin() == TRUE ? ERR_NONE : ERR_PLAYER_STATE_LOGIN;
	if (err == ERR_NONE) pPlayer->SetFlags(clientFlags.flags());
	if (err == ERR_NONE) serverFlags.set_flags(clientFlags.flags());

	serverFlags.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverFlags, ::Server::SERVER_MSG::FLAGS);

	//
	// 4. 发送玩家
	//
	SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
}
*/

//
// 创建游戏
//
void CGameServer::OnCreateGame(CPlayer *pPlayer, WORD size)
{
	::Client::CreateGame clientCreateGame;
	::Server::CreateGame serverCreateGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientCreateGame, size) == FALSE) {
		return;
	}

	//
	// 2. 创建游戏
	//
	int err = ERR_NONE;
	CGame *pGame = GetNextGame();
	
	if (err == ERR_NONE) err = pGame ? ERR_NONE : ERR_SERVER_FULL;
	if (err == ERR_NONE) pPlayer->GetFlags() == PLAYER_FLAGS_LOGIN ? ERR_NONE : ERR_PLAYER_STATE_LOGIN;
	if (err == ERR_NONE) pGame->SetGame(clientCreateGame.password().c_str(), clientCreateGame.mode(), clientCreateGame.map(), clientCreateGame.maxplayers());
	if (err == ERR_NONE) err = pGame->AddPlayer(pPlayer, clientCreateGame.password().c_str(), TRUE);
	if (err != ERR_NONE) ReleaseGame(pGame);

	serverCreateGame.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverCreateGame, ::Server::SERVER_MSG::CREATE_GAME);

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
	::Client::DestroyGame clientDestroyGame;
	::Server::DestroyGame serverDestroyGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientDestroyGame, size) == FALSE) {
		return;
	}

	//
	// 2. 销毁检查
	//
	int err = pPlayer->pGame ? ERR_NONE : ERR_PLAYER_OUT_GAME;
	serverDestroyGame.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverDestroyGame, ::Server::SERVER_MSG::DESTROY_GAME);

	//
	// 4. 发送玩家
	//
	if (err == ERR_NONE) {
		SendToPlayerAll(pPlayer->pGame, NULL, buffer, writeBuffer.GetActiveBufferSize());
	}
	else {
		SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
	}

	//
	// 5. 销毁游戏
	//
	if (err == ERR_NONE) {
		ReleaseGame(pPlayer->pGame);
	}
}

//
// 进入游戏
//
void CGameServer::OnEnterGame(CPlayer *pPlayer, WORD size)
{
	::Client::EnterGame clientEnterGame;
	::Server::EnterGame serverEnterGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientEnterGame, size) == FALSE) {
		return;
	}

	//
	// 2. 进入游戏
	//
	int err = ERR_NONE;

	if (err == ERR_NONE) pPlayer->GetFlags() == PLAYER_FLAGS_LOGIN ? ERR_NONE : ERR_PLAYER_STATE_LOGIN;
	if (err == ERR_NONE) err = clientEnterGame.gameid() >= 0 && clientEnterGame.gameid() < m_maxGames ? ERR_NONE : ERR_GAME_INVALID_ID;
	if (err == ERR_NONE) err = m_games[clientEnterGame.gameid()]->AddPlayer(pPlayer, clientEnterGame.password().c_str(), FALSE);

	serverEnterGame.set_err(err);
	serverEnterGame.set_guid(pPlayer->guid);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverEnterGame, ::Server::SERVER_MSG::ENTER_GAME);

	//
	// 4. 发送玩家
	//
	if (err == ERR_NONE) {
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
	::Client::ExitGame clientExitGame;
	::Server::ExitGame serverExitGame;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientExitGame, size) == FALSE) {
		return;
	}

	//
	// 2. 退出游戏
	//
	int err = pPlayer->pGame ? ERR_NONE : ERR_PLAYER_OUT_GAME;
	serverExitGame.set_err(err);
	serverExitGame.set_guid(pPlayer->guid);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverExitGame, ::Server::SERVER_MSG::EXIT_GAME);

	//
	// 4. 发送玩家
	//
	if (err == ERR_NONE) {
		SendToPlayerAll(pPlayer->pGame, NULL, buffer, writeBuffer.GetActiveBufferSize());
	}
	else {
		SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
	}

	//
	// 5. 退出游戏
	//
	if (err == ERR_NONE) {
		pPlayer->pGame->DelPlayer(pPlayer);
	}
}

//
// 修改游戏密码
//
void CGameServer::OnModifyGamePassword(CPlayer *pPlayer, WORD size)
{
	::Client::ModifyGamePassword clientModifyGamePassword;
	::Server::ModifyGamePassword serverModifyGamePassword;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientModifyGamePassword, size) == FALSE) {
		return;
	}

	//
	// 2. 修改游戏密码
	//
	int err = ERR_NONE;

	if (err == ERR_NONE) err = pPlayer->pGame ? ERR_NONE : ERR_PLAYER_OUT_GAME;
	if (err == ERR_NONE) pPlayer->pGame->SetGame(clientModifyGamePassword.password().c_str(), pPlayer->pGame->GetMode(), pPlayer->pGame->GetMapID(), pPlayer->pGame->GetMaxPlayers());

	serverModifyGamePassword.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverModifyGamePassword, ::Server::SERVER_MSG::MODIFY_GAME_PASSWORD);

	//
	// 4. 发送玩家
	//
	SendToPlayer(pPlayer, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 发送指定玩家
//
void CGameServer::OnSendToPlayer(CPlayer *pPlayer, WORD size)
{
	::Client::SendToPlayer clientSendToPlayer;
	::Server::SendToPlayer serverSendToPlayer;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientSendToPlayer, size) == FALSE) {
		return;
	}

	//
	// 2. 查找目标玩家
	//
	CPlayer *pTarget = QueryPlayer(clientSendToPlayer.guid());
	if (pTarget == NULL) return;

	serverSendToPlayer.set_size(clientSendToPlayer.size());
	serverSendToPlayer.set_data(clientSendToPlayer.data().c_str(), clientSendToPlayer.size());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverSendToPlayer, ::Server::SERVER_MSG::SEND_TO_PLAYER);

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
	::Client::SendToPlayerAll clientSendToPlayerAll;
	::Server::SendToPlayer serverSendToPlayer;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pPlayer->recvBuffer, &clientSendToPlayerAll, size) == FALSE) {
		return;
	}

	//
	// 2. 查找目标玩家
	//
	if (pPlayer->pGame == NULL) {
		return;
	}

	serverSendToPlayer.set_size(clientSendToPlayerAll.size());
	serverSendToPlayer.set_data(clientSendToPlayerAll.data().c_str(), clientSendToPlayerAll.size());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &serverSendToPlayer, ::Server::SERVER_MSG::SEND_TO_PLAYER);

	//
	// 4. 发送所有玩家
	//
	SendToPlayerAll(pPlayer->pGame, pPlayer, buffer, writeBuffer.GetActiveBufferSize(), clientSendToPlayerAll.filter());
}
