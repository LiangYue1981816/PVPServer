#include "GateServer.h"


//
// 客户端链接回调
//
void CGateServer::OnConnect(CIOContext *pContext, SOCKET acceptSocket)
{
	CIOCPServer::OnConnect(pContext, acceptSocket);
}

//
// 客户端断链回调
//
void CGateServer::OnDisconnect(CIOContext *pContext)
{
	Logout(pContext);
	ClearGameServer(pContext);
	CIOCPServer::OnDisconnect(pContext);
}

//
// 更新接收消息
//
void CGateServer::OnUpdateRecv(DWORD dwDeltaTime)
{
	CIOContext *pContext = m_pActiveContext;

	while (pContext) {
		CIOContext *pNextContext = pContext->pNextActive;

		if (pContext->IsAlive()) {
			pContext->SwitchRecvBuffer();
			pContext->dwHeartTime += dwDeltaTime;

			while (TRUE) {
				WORD msg;
				WORD fullSize;
				WORD bodySize;

				if (pContext->GetRecvBuffer().GetData((BYTE *)&fullSize, sizeof(fullSize)) != sizeof(fullSize)) break;
				if (pContext->GetRecvBuffer().GetActiveBufferSize() < sizeof(fullSize) + fullSize) break;

				if (pContext->GetRecvBuffer().PopData((BYTE *)&fullSize, sizeof(fullSize)) != sizeof(fullSize)) break;
				if (pContext->GetRecvBuffer().PopData((BYTE *)&msg, sizeof(msg)) != sizeof(msg))  break;

				bodySize = fullSize - sizeof(msg);
				m_dwRecvDataSize += sizeof(fullSize) + fullSize;

				ResponseFuncs::const_iterator itFunc = m_responses.find(msg);
				if (itFunc == m_responses.end()) continue;

				(this->*itFunc->second)(pContext, bodySize);
				OnHeartReset(pContext);
			}
		}

		if (pContext->Check((DWORD)(1000 * m_timeOut)) == FALSE) {
			ReleaseContext(pContext, FALSE);
		}

		pContext = pNextContext;
	}
}

//
// 更新匹配
//
void CGateServer::OnUpdateMatch(DWORD dwDeltaTime)
{

}

//
// 重置心跳
//
void CGateServer::OnHeartReset(CIOContext *pContext)
{
	pContext->dwHeartTime = 0;
}

//
// 心跳
//
void CGateServer::OnHeart(CIOContext *pContext, WORD size)
{
	ProtoGateClient::Heart requestHeart;
	ProtoGateServer::Heart responseHeart;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->GetRecvBuffer(), &requestHeart, size) == FALSE) {
		return;
	}

	//
	// 2. 心跳
	//
	responseHeart.set_timestamp(requestHeart.timestamp());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseHeart, ProtoGateServer::RESPONSE_MSG::HEART);

	//
	// 4. 发送
	//
	SendTo(pContext, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 登陆
//
void CGateServer::OnLogin(CIOContext *pContext, WORD size)
{
	ProtoGateClient::Login requestLogin;
	ProtoGateServer::Login responseLogin;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->GetRecvBuffer(), &requestLogin, size) == FALSE) {
		return;
	}

	//
	// 2. 登陆
	//
	ProtoGateServer::ERROR_CODE err = ProtoGateServer::ERROR_CODE::ERR_NONE;

	if (requestLogin.version() != ProtoGateServer::VERSION_NUMBER::VERSION) {
		err = ProtoGateServer::ERROR_CODE::ERR_VERSION_INVALID; goto ERR;
	}

	if (pContext->guid != 0xffffffff) {
		err = ProtoGateServer::ERROR_CODE::ERR_PLAYER_NOT_NONE; goto ERR;
	}

	if (Login(pContext, requestLogin.guid()) == FALSE) {
		err = ProtoGateServer::ERROR_CODE::ERR_PLAYER_INVALID_GUID; goto ERR;
	}

	responseLogin.set_guid(pContext->guid);

	goto NEXT;
ERR:
NEXT:
	responseLogin.set_err(err);

	 //
	 // 3. 序列化消息
	 //
	 Serializer(&writeBuffer, &responseLogin, ProtoGateServer::RESPONSE_MSG::LOGIN);

	 //
	 // 4. 发送
	 //
	 SendTo(pContext, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 匹配
//
void CGateServer::OnMatch(CIOContext *pContext, WORD size)
{
	ProtoGateClient::Match requestMatch;
	ProtoGateServer::Match responseMatch;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->GetRecvBuffer(), &requestMatch, size) == FALSE) {
		return;
	}

	//
	// 2. 检查
	//
	ProtoGateServer::ERROR_CODE err = ProtoGateServer::ERROR_CODE::ERR_NONE;

	if (pContext->guid == 0xffffffff) {
		err = ProtoGateServer::ERROR_CODE::ERR_PLAYER_NOT_LOGIN; goto ERR;
	}

	if (requestMatch.evaluation() < m_minEvaluation || requestMatch.evaluation() > m_maxEvaluation) {
		err = ProtoGateServer::ERROR_CODE::ERR_MATCH_INVALID_EVALUATION; goto ERR;
	}

	goto NEXT;
ERR:
	responseMatch.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseMatch, ProtoGateServer::RESPONSE_MSG::MATCH);

	//
	// 4. 发送
	//
	SendTo(pContext, buffer, writeBuffer.GetActiveBufferSize());

	return;
NEXT:

	//
	// 5. 添加到待匹配玩家集合
	//
	if (pContext->dwUserData == 0xffffffff) {
		std::map<DWORD, PlayerStatus>::const_iterator itPlayer = m_evaluations[requestMatch.evaluation()].find(pContext->guid);
		if (itPlayer != m_evaluations[requestMatch.evaluation()].end()) return;

		m_evaluations[requestMatch.evaluation()][pContext->guid].pContext = pContext;
		m_evaluations[requestMatch.evaluation()][pContext->guid].timeout = 0.0f;
		m_evaluations[requestMatch.evaluation()][pContext->guid].minEvaluation = requestMatch.evaluation();
		m_evaluations[requestMatch.evaluation()][pContext->guid].maxEvaluation = requestMatch.evaluation();

		pContext->dwUserData = requestMatch.evaluation();
	}
}

//
// 取消匹配
//
void CGateServer::OnCancelMatch(CIOContext *pContext, WORD size)
{
	ProtoGateClient::CancelMatch requestCancelMatch;
	ProtoGateServer::CancelMatch responseCancelMatch;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->GetRecvBuffer(), &requestCancelMatch, size) == FALSE) {
		return;
	}

	//
	// 2. 取消匹配
	//
	if (pContext->dwUserData != 0xffffffff) {
		PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.find(pContext->dwUserData);
		if (itPlayerMap != m_evaluations.end()) {
			std::map<DWORD, PlayerStatus>::iterator itPlayer = itPlayerMap->second.find(pContext->guid);
			if (itPlayer != itPlayerMap->second.end()) itPlayerMap->second.erase(itPlayer);
			if (itPlayerMap->second.empty()) m_evaluations.erase(itPlayerMap);
		}

		pContext->dwUserData = 0xffffffff;
	}

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseCancelMatch, ProtoGateServer::RESPONSE_MSG::CANCEL_MATCH);

	//
	// 4. 发送
	//
	SendTo(pContext, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 游戏服务器列表
//
void CGateServer::OnListGameServer(CIOContext *pContext, WORD size)
{
	ProtoGateClient::ListGameServer requestListGameServer;
	ProtoGateServer::ListGameServer responseListGameServer;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->GetRecvBuffer(), &requestListGameServer, size) == FALSE) {
		return;
	}

	//
	// 2. 获得游戏服务器列表
	//
	ProtoGateServer::ERROR_CODE err = ProtoGateServer::ERROR_CODE::ERR_NONE;

	if (pContext->guid == 0xffffffff) {
		err = ProtoGateServer::ERROR_CODE::ERR_PLAYER_NOT_LOGIN; goto ERR;
	}

	for (GameServerMap::const_iterator itGameServer = m_servers.begin(); itGameServer != m_servers.end(); ++itGameServer) {
		if (ProtoGateServer::ListGameServer_GameServer *pGameServer = responseListGameServer.add_servers()) {
			pGameServer->set_ip(itGameServer->second.ip);
			pGameServer->set_port(itGameServer->second.port);
			pGameServer->set_curgames(itGameServer->second.curGames);
			pGameServer->set_maxgames(itGameServer->second.maxGames);
		}
	}

	goto NEXT;
ERR:
NEXT:
	responseListGameServer.set_err(err);

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseListGameServer, ProtoGateServer::RESPONSE_MSG::LIST_GAME_SERVER);

	//
	// 4. 发送
	//
	SendTo(pContext, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 发送指定玩家
//
void CGateServer::OnSendToPlayer(CIOContext *pContext, WORD size)
{
	ProtoGateClient::SendToPlayer requestSendToPlayer;
	ProtoGateServer::SendToPlayer responseSendToPlayer;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->GetRecvBuffer(), &requestSendToPlayer, size) == FALSE) {
		return;
	}

	//
	// 2. 转发协议
	//
	if (pContext->guid == 0xffffffff) {
		return;
	}

	responseSendToPlayer.set_size(requestSendToPlayer.size());
	responseSendToPlayer.set_data(requestSendToPlayer.data().c_str(), requestSendToPlayer.size());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseSendToPlayer, ProtoGateServer::RESPONSE_MSG::SEND_TO_PLAYER);

	//
	// 4. 发送指定玩家
	//
	if (requestSendToPlayer.guids_size() > 0) {
		for (int index = 0; index < requestSendToPlayer.guids_size(); index++) {
			if (CIOContext *pContextSendTo = QueryContext(requestSendToPlayer.guids(index))) {
				if (pContext != pContextSendTo) {
					SendTo(pContextSendTo, buffer, writeBuffer.GetActiveBufferSize());
				}
			}
		}
	}
	else {
		for (PlayerMap::const_iterator itPlayer = m_players.begin(); itPlayer != m_players.end(); ++itPlayer) {
			if (pContext != itPlayer->second) {
				SendTo(itPlayer->second, buffer, writeBuffer.GetActiveBufferSize());
			}
		}
	}
}

//
// 游戏服务器状态
//
void CGateServer::OnGameServerStatus(CIOContext *pContext, WORD size)
{
	ProtoGameServer::ServerStatus requestServerStatus;

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->GetRecvBuffer(), &requestServerStatus, size) == FALSE) {
		return;
	}

	//
	// 2. 更新游戏服务器列表
	//
	strcpy(m_servers[pContext].ip, requestServerStatus.ip().c_str());
	m_servers[pContext].port = requestServerStatus.port();
	m_servers[pContext].curGames = requestServerStatus.curgames();
	m_servers[pContext].maxGames = requestServerStatus.maxgames();

	m_servers[pContext].games.clear();
	for (int index = 0; index < requestServerStatus.games_size(); index++) {
		GameStatus gameStatus;
		gameStatus.bEmpty = requestServerStatus.games(index).empty() ? TRUE : FALSE;
		gameStatus.id = requestServerStatus.games(index).gameid();
		gameStatus.mode = requestServerStatus.games(index).mode();
		gameStatus.mapid = requestServerStatus.games(index).mapid();
		gameStatus.evaluation = requestServerStatus.games(index).evaluation();
		m_servers[pContext].games.push_back(gameStatus);
	}
}

//
// 输出日志
//
void WriteLog(const char *szFmt, ...)
{
	va_list argList;
	static char szString[1024 * 1024];

	va_start(argList, szFmt);
	vsprintf(szString, szFmt, argList);

	time_t timeRaw;
	struct tm *timeInfo;
	time(&timeRaw);
	timeInfo = localtime(&timeRaw);

	char szFileName[260];
	sprintf(szFileName, "GateServer%d-%02d-%02d.log", timeInfo->tm_year + 1900, timeInfo->tm_mon + 1, timeInfo->tm_mday);

	if (FILE *pFile = fopen(szFileName, "a+")) {
		fprintf(pFile, "%02d:%02d:%02d: %s", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec, szString);
		fclose(pFile);
	}

	printf("%s", szString);
}
