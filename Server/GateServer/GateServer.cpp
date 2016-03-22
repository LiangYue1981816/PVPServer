#include "GateServer.h"


CGateServer::CGateServer(void)
	: m_timeOut(0)
	, m_hUpdateThread(NULL)

	, m_dwUpdateCount(0)
	, m_dwUpdateTime(0)
	, m_dwUpdateTimeTotal(0)
	, m_dwRuntimeTotal(0)

	, m_dwRecvDataSize(0)
	, m_dwSendDataSize(0)
{

}

CGateServer::~CGateServer(void)
{

}

//
// 启动服务器
//
BOOL CGateServer::Start(const char *ip, int port, int maxContexts, int timeOut)
{
	//
	// 1. 保存超时设置
	//
	m_timeOut = max(5, timeOut);

	//
	// 2. 启动服务器
	//
	if (AllocContexts(maxContexts) == FALSE) return FALSE;
	if (Listen(ip, port) == FALSE) goto ERR;
	if (CreateIOCP() == FALSE) goto ERR;
	if (CreateShutdownEvent() == FALSE) goto ERR;
	if (CreateListenThread() == FALSE) goto ERR;
	if (CreateTransferThreads() == FALSE) goto ERR;
	if (CreateUpdateThread() == FALSE) goto ERR;

	goto RET;
ERR:
	WriteLog("Start fail err = %d", WSAGetLastError());
	return FALSE;
RET:
	return TRUE;
}

//
// 停止服务器
//
void CGateServer::Stop(void)
{
	m_timeOut = 0;

	SetEvent(m_hShutdownEvent);

	Disconnect();
	DestroyIOCP();
	DestroyListenThread();
	DestroyTransferThreads();
	DestroyUpdateThread();
	DestroyShutdownEvent();
	FreeContexts();
}

//
// 创建更新线程
//
BOOL CGateServer::CreateUpdateThread(void)
{
	m_hUpdateThread = CreateThread(0, 0, UpdateThread, (LPVOID)this, 0, NULL);
	return m_hUpdateThread != NULL ? TRUE : FALSE;
}

//
// 销毁更新线程
//
void CGateServer::DestroyUpdateThread(void)
{
	if (m_hUpdateThread) {
		WaitForSingleObject(m_hUpdateThread, INFINITE);
		CloseHandle(m_hUpdateThread);
		m_hUpdateThread = NULL;
	}
}

//
// 发送指定客户端
//
void CGateServer::SendTo(CIOContext *pContext, BYTE *pBuffer, size_t size)
{
	if (pContext && pContext->IsAlive() && pBuffer && size > 0) {
		pContext->sendBuffer.Lock();
		pContext->sendBuffer.PushData(pBuffer, size);
		pContext->sendBuffer.Unlock();

		m_dwSendDataSize += (DWORD)size;
	}
}

//
// 客户端断链回调
//
void CGateServer::OnDisconnect(CIOContext *pContext)
{
	GameServerMap::const_iterator itGameServer = m_gameServerMap.find(pContext);
	if (itGameServer != m_gameServerMap.end()) m_gameServerMap.erase(itGameServer);

	CIOCPServer::OnDisconnect(pContext);
}

//
// 更新发送消息
//
void CGateServer::OnUpdateSend(void)
{
	if (CIOContext *pContext = m_pActiveContext) {
		do {
			if (pContext->IsAlive()) {
				pContext->sendBuffer.Lock();
				{
					pContext->OnSendNext(NULL, 0, 0);
				}
				pContext->sendBuffer.Unlock();
			}
		} while (pContext = pContext->pNextActive);
	}
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
			pContext->recvBuffer.Lock();
			{
				pContext->dwHeartTime += dwDeltaTime;

				while (TRUE) {
					WORD msg = 0;
					WORD fullSize = *(WORD *)pContext->recvBuffer.GetPopPointer();
					WORD bodySize = fullSize - sizeof(msg);

					if (pContext->recvBuffer.GetActiveBufferSize() < sizeof(fullSize) + fullSize) break;
					if (pContext->recvBuffer.PopData((BYTE *)&fullSize, sizeof(fullSize)) == FALSE) break;
					if (pContext->recvBuffer.PopData((BYTE *)&msg, sizeof(msg)) == FALSE)  break;

					switch (msg) {
					case ProtoGateClient::REQUEST_MSG::HEART:
						OnHeart(pContext, bodySize);
						OnHeartReset(pContext);
						break;

					case ProtoGateClient::REQUEST_MSG::GAME_SERVER_LIST:
						OnGameServerList(pContext, bodySize);
						OnHeartReset(pContext);
						break;

					case ProtoGameServer::REQUEST_MSG::GAME_LIST:
						OnGameList(pContext, bodySize);
						OnHeartReset(pContext);
						break;
					}
				}
			}
			pContext->recvBuffer.Unlock();
		}

		if (pContext->dwHeartTime > (DWORD)(1000 * m_timeOut)) {
			WriteLog("%s: Heart TimeOut\n", pContext->ip);
			ReleaseIOContext(pContext, FALSE);
		}

		pContext = pNextContext;
	}
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
	if (Parser(&pContext->recvBuffer, &requestHeart, size) == FALSE) {
		return;
	}

	//
	// 2. 心跳
	//
	responseHeart.set_timestamp(requestHeart.timestamp());

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseHeart, ProtoGameServer::RESPONSE_MSG::HEART);

	//
	// 4. 发送
	//
	SendTo(pContext, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 获得游戏服务器列表
//
void CGateServer::OnGameServerList(CIOContext *pContext, WORD size)
{
	ProtoGateClient::GameServerList requestGameServerList;
	ProtoGateServer::GameServerList responseGameServerList;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->recvBuffer, &requestGameServerList, size) == FALSE) {
		return;
	}

	//
	// 2. 游戏服务器列表
	//
	for (GameServerMap::const_iterator itGameServer = m_gameServerMap.begin(); itGameServer != m_gameServerMap.end(); ++itGameServer) {
		if (ProtoGateServer::GameServerList_GameServer *pGameServer = responseGameServerList.add_servers()) {
			pGameServer->set_ip(itGameServer->second.ip);
			pGameServer->set_port(itGameServer->second.port);

			for (std::vector<Game>::const_iterator itGame = itGameServer->second.games.begin(); itGame != itGameServer->second.games.end(); ++itGame) {
				if (ProtoGateServer::GameServerList_GameServer_Game *pGame = pGameServer->add_games()) {
					pGame->set_private_(itGame->bPrivate ? true : false);
					pGame->set_gameid(itGame->gameid);
					pGame->set_mode(itGame->mode);
					pGame->set_map(itGame->mapid);
					pGame->set_maxplayers(itGame->maxPlayers);
					
					for (std::vector<int>::const_iterator itPlayer = itGame->players.begin(); itPlayer != itGame->players.end(); ++itPlayer) {
						pGame->add_playes(*itPlayer);
					}
				}
			}
		}
	}

	//
	// 3. 序列化消息
	//
	Serializer(&writeBuffer, &responseGameServerList, ProtoGameServer::RESPONSE_MSG::HEART);

	//
	// 4. 发送
	//
	SendTo(pContext, buffer, writeBuffer.GetActiveBufferSize());
}

//
// 游戏列表
//
void CGateServer::OnGameList(CIOContext *pContext, WORD size)
{
	ProtoGameServer::GameList requestGameList;

	//
	// 1. 解析消息
	//
	if (Parser(&pContext->recvBuffer, &requestGameList, size) == FALSE) {
		return;
	}

	//
	// 2. 更新游戏服务器列表
	//
	m_gameServerMap[pContext].games.clear();

	strcpy(m_gameServerMap[pContext].ip, requestGameList.ip().c_str());
	m_gameServerMap[pContext].port = requestGameList.port();

	for (int indexGame = 0; indexGame < requestGameList.games_size(); indexGame++) {
		Game game;
		game.bPrivate = requestGameList.games(indexGame).private_() ? TRUE : FALSE;
		game.gameid = requestGameList.games(indexGame).gameid();
		game.mapid = requestGameList.games(indexGame).map();
		game.mode = requestGameList.games(indexGame).mode();
		game.maxPlayers = requestGameList.games(indexGame).maxplayers();
		for (int indexPlayer = 0; indexPlayer < requestGameList.games(indexGame).playes_size(); indexPlayer++) {
			game.players.push_back(requestGameList.games(indexGame).playes(indexPlayer));
		}
		m_gameServerMap[pContext].games.push_back(game);
	}
}

//
// 监控
//
void CGateServer::Monitor(void)
{
	//
	// 1. 清屏幕
	//
	system("cls");

	//
	// 2. 显示服务器状态
	//
	printf("Recv Data = %dB (%2.2fMb/s)\n", m_dwRecvDataSize, 8.0f*m_dwRecvDataSize / 1024.0f / 1024.0f);
	printf("Send Data = %dB (%2.2fMb/s)\n", m_dwSendDataSize, 8.0f*m_dwSendDataSize / 1024.0f / 1024.0f);
	printf("Update Time = %dms\n", m_dwUpdateTime);
	printf("Run Time = %2.2d:%2.2d:%2.2d\n", m_dwRuntimeTotal / 3600, m_dwRuntimeTotal / 60 - (m_dwRuntimeTotal / 3600) * 60, m_dwRuntimeTotal - (m_dwRuntimeTotal / 60) * 60);
}

//
// 更新线程
//
DWORD WINAPI CGateServer::UpdateThread(LPVOID lpParam)
{
	if (CGateServer *pServer = (CGateServer *)lpParam) {
		while (WAIT_OBJECT_0 != WaitForSingleObject(pServer->m_hShutdownEvent, 0)) {
			DWORD dwLastTime = tick() / 1000;
			static DWORD dwDeltaTime = 0;
			static DWORD dwGameDeltaTime = 0;
			static DWORD dwReportDeltaTime = 0;
			{
				//
				// 1. 更新服务器
				//
				DWORD dwBegin = tick() / 1000;
				EnterCriticalSection(&pServer->m_sectionIOContext);
				{
					pServer->OnUpdateRecv(dwDeltaTime);
					pServer->OnUpdateSend();
				}
				LeaveCriticalSection(&pServer->m_sectionIOContext);
				DWORD dwEnd = tick() / 1000;

				//
				// 2. 更新统计信息
				//
				pServer->m_dwUpdateCount++;
				pServer->m_dwUpdateTimeTotal += dwEnd - dwBegin;
				pServer->m_dwUpdateTime = pServer->m_dwUpdateTimeTotal / pServer->m_dwUpdateCount;

				// 报告更新1FPS
				if (dwReportDeltaTime > 1000) {
					EnterCriticalSection(&pServer->m_sectionIOContext);
					{
						pServer->Monitor();
					}
					LeaveCriticalSection(&pServer->m_sectionIOContext);

					pServer->m_dwRuntimeTotal++;
					pServer->m_dwUpdateCount = 0;
					pServer->m_dwUpdateTime = 0;
					pServer->m_dwUpdateTimeTotal = 0;
					pServer->m_dwRecvDataSize = 0;
					pServer->m_dwSendDataSize = 0;

					dwReportDeltaTime = 0;
				}

				//
				// 3. 释放时间片
				//
				Sleep(1);
			}
			dwDeltaTime = tick() / 1000 - dwLastTime;
			dwDeltaTime = dwDeltaTime < 1000 ? dwDeltaTime : 0;
			dwGameDeltaTime += dwDeltaTime;
			dwReportDeltaTime += dwDeltaTime;
		}
	}

	return 0L;
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
