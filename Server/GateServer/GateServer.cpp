#include "GateServer.h"


CGateServer::CGateServer(void)
	: m_hUpdateThread(NULL)

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
// 登陆
//
BOOL CGateServer::Login(CIOContext *pContext, DWORD guid)
{
	//
	// 1. 参数安全检查
	//
	if (guid == 0xffffffff) {
		return FALSE;
	}

	//
	// 2. 查找
	//
	PlayerMap::const_iterator itPlayer = m_players.find(guid);
	if (itPlayer != m_players.end()) return FALSE;

	//
	// 3. 登陆
	//
	PlayerStatus player;
	player.pContext = pContext;
	player.pContext->guid = guid;
	player.evaluation = 0;
	player.timeout = 0.0f;

	m_players[guid] = player;

	return TRUE;
}

//
// 注销
//
BOOL CGateServer::Logout(CIOContext *pContext)
{
	//
	// 1. 注销玩家集合
	//
	PlayerMap::const_iterator itPlayer = m_players.find(pContext->guid);
	if (itPlayer != m_players.end()) m_players.erase(itPlayer);

	//
	// 2. 注销匹配集合
	//
	PlayerMap::const_iterator itMatch = m_matchs.find(pContext->guid);
	if (itMatch != m_matchs.end()) m_matchs.erase(itMatch);

	//
	// 3. 恢复初始化
	//
	pContext->guid = 0xffffffff;

	return TRUE;
}

//
// 查询
//
CIOContext* CGateServer::QueryContext(DWORD guid)
{
	PlayerMap::const_iterator itPlayer = m_players.find(guid);
	return itPlayer != m_players.end() ? itPlayer->second.pContext : NULL;
}

//
// 清理游戏服务器
//
void CGateServer::ClearGameServer(CIOContext *pContext)
{
	GameServerMap::const_iterator itGameServer = m_servers.find(pContext);
	if (itGameServer != m_servers.end()) m_servers.erase(itGameServer);
}

//
// 发送指定客户端
//
void CGateServer::SendTo(CIOContext *pContext, BYTE *pBuffer, size_t size)
{
	if (pContext && pContext->IsAlive() && pBuffer && size > 0) {
		pContext->Send(pBuffer, size);
		m_dwSendDataSize += (DWORD)size;
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
	printf("GateServer %s:%d\n", m_ip, m_port);
	printf("Recv Data = %dB (%2.2fMb/s)\n", m_dwRecvDataSize, 8.0f * m_dwRecvDataSize / 1024.0f / 1024.0f);
	printf("Send Data = %dB (%2.2fMb/s)\n", m_dwSendDataSize, 8.0f * m_dwSendDataSize / 1024.0f / 1024.0f);
	printf("Update Time = %dms\n", m_dwUpdateTime);
	printf("Run Time = %2.2d:%2.2d:%2.2d\n", m_dwRuntimeTotal / 3600, m_dwRuntimeTotal / 60 - (m_dwRuntimeTotal / 3600) * 60, m_dwRuntimeTotal - (m_dwRuntimeTotal / 60) * 60);
	printf("GameServers = %d, Players = %d/%d\n", m_servers.size(), m_players.size(), m_maxContexts);
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
				EnterCriticalSection(&pServer->m_sectionContext);
				{
					//
					// 1. 更新服务器
					//
					DWORD dwBegin = tick() / 1000;
					{
						pServer->OnUpdateRecv(dwDeltaTime);
						pServer->OnUpdateMatch(dwDeltaTime);
						pServer->OnUpdateSend();
					}
					DWORD dwEnd = tick() / 1000;

					//
					// 2. 更新统计信息
					//
					pServer->m_dwUpdateCount++;
					pServer->m_dwUpdateTimeTotal += dwEnd - dwBegin;
					pServer->m_dwUpdateTime = pServer->m_dwUpdateTimeTotal / pServer->m_dwUpdateCount;

					// 报告更新1FPS
					if (dwReportDeltaTime > 1000) {
						pServer->Monitor();
						pServer->m_dwRuntimeTotal++;
						pServer->m_dwUpdateCount = 0;
						pServer->m_dwUpdateTime = 0;
						pServer->m_dwUpdateTimeTotal = 0;
						pServer->m_dwRecvDataSize = 0;
						pServer->m_dwSendDataSize = 0;

						dwReportDeltaTime = 0;
					}
				}
				LeaveCriticalSection(&pServer->m_sectionContext);

				//
				// 3. 释放时间片
				//
				timeBeginPeriod(1);
				{
					Sleep(1);
				}
				timeEndPeriod(1);
			}
			dwDeltaTime = tick() / 1000 - dwLastTime;
			dwDeltaTime = dwDeltaTime < 1000 ? dwDeltaTime : 0;
			dwGameDeltaTime += dwDeltaTime;
			dwReportDeltaTime += dwDeltaTime;
		}
	}

	return 0L;
}
