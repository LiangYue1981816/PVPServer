#include "GameServer.h"


CGameServer::CGameServer(void)
	: m_maxGames(0)
	, m_games(NULL)
	, m_pFreeGame(NULL)
	, m_pActiveGame(NULL)

	, m_timeOut(0)

	, m_hReportThread(NULL)
	, m_hUpdateThread(NULL)

	, m_dwUpdateCount(0)
	, m_dwUpdateTime(0)
	, m_dwUpdateTimeTotal(0)
	, m_dwRuntimeTotal(0)

	, m_dwRecvDataSize(0)
	, m_dwSendDataSize(0)
{
	m_nRootServerPort = 0;
	memset(m_szRootServerIP, 0, sizeof(m_szRootServerIP));
}

CGameServer::~CGameServer(void)
{

}

//
// 启动服务器
//
BOOL CGameServer::Start(const char *ip, int port, int maxGames, int maxPlayers, int timeOut, const char *rootip, int rootport)
{
	//
	// 1. 保存超时设置
	//
	m_timeOut = max(1000, timeOut);

	//
	// 2. 保存入口服务器地址
	//
	m_nRootServerPort = rootport;
	strcpy(m_szRootServerIP, rootip);

	//
	// 3. 启动服务器
	//
	if (AllocGames(maxGames) == FALSE) return FALSE;
	if (AllocPlayers(maxPlayers) == FALSE) return FALSE;
	if (Listen(ip, port) == FALSE) return FALSE;
	if (CreateIOCP() == FALSE) return FALSE;
	if (CreateWorkThreads() == FALSE) return FALSE;
	if (CreateReportThread() == FALSE) return FALSE;
	if (CreateUpdateThread() == FALSE) return FALSE;

	return TRUE;
}

//
// 停止服务器
//
void CGameServer::Stop(void)
{
	m_timeOut = 0;

	m_nRootServerPort = 0;
	memset(m_szRootServerIP, 0, sizeof(m_szRootServerIP));

	Disconnect();
	DestroyIOCP();
	DestroyWorkThreads();
	DestroyReportThread();
	DestroyUpdateThread();
	FreeGames();
	FreePlayers();
}

//
// 分配游戏
//
BOOL CGameServer::AllocGames(int maxGames)
{
	//
	// 1. 分配游戏存储
	//
	m_maxGames = maxGames;
	m_games = new CGame*[m_maxGames];

	//
	// 2. 建立游戏链表
	//
	for (int indexGame = 0; indexGame < m_maxGames; indexGame++) {
		m_games[indexGame] = new CGame(this);
	}

	for (int indexGame = 0; indexGame < m_maxGames - 1; indexGame++) {
		m_games[indexGame]->pNext = m_games[indexGame + 1];
		m_games[indexGame + 1]->pNext = NULL;
	}

	m_pFreeGame = m_games[0];
	m_pActiveGame = NULL;

	return TRUE;
}

//
// 分配玩家
//
BOOL CGameServer::AllocPlayers(int maxPlayers)
{
	//
	// 1. 分配IO上下文存储
	//
	m_curContexts = 0;
	m_maxContexts = maxPlayers;
	m_contexts = new CIOContext*[m_maxContexts];

	//
	// 2. 建立玩家链表
	//
	for (int indexContext = 0; indexContext < m_maxContexts; indexContext++) {
		m_contexts[indexContext] = new CPlayer(this);
		m_contexts[indexContext]->id = indexContext;
	}

	for (int indexContext = 0; indexContext < m_maxContexts - 1; indexContext++) {
		m_contexts[indexContext]->pNext = m_contexts[indexContext + 1];
		m_contexts[indexContext + 1]->pNext = NULL;
	}

	m_pFreeContext = m_contexts[0];
	m_pActiveContext = NULL;

	return TRUE;
}

//
// 创建汇报线程
//
BOOL CGameServer::CreateReportThread(void)
{
	m_hReportThread = CreateThread(0, 0, ReportThread, (LPVOID)this, 0, NULL);
	return m_hReportThread != NULL ? TRUE : FALSE;
}

//
// 创建更新线程
//
BOOL CGameServer::CreateUpdateThread(void)
{
	m_hUpdateThread = CreateThread(0, 0, UpdateThread, (LPVOID)this, 0, NULL);
	return m_hUpdateThread != NULL ? TRUE : FALSE;
}

//
// 释放游戏
//
void CGameServer::FreeGames(void)
{
	if (m_games) {
		for (int indexGame = 0; indexGame < m_maxGames; indexGame++) {
			delete m_games[indexGame];
		}

		delete [] m_games;
	}

	m_maxGames = 0;

	m_games = NULL;
	m_pFreeGame = NULL;
	m_pActiveGame = NULL;
}

//
// 释放玩家
//
void CGameServer::FreePlayers(void)
{
	if (m_contexts) {
		for (int indexContext = 0; indexContext < m_maxContexts; indexContext++) {
			delete m_contexts[indexContext];
		}

		delete [] m_contexts;
	}

	m_curContexts = 0;
	m_maxContexts = 0;

	m_contexts = NULL;
	m_pFreeContext = NULL;
	m_pActiveContext = NULL;
}

//
// 销毁汇报线程
//
void CGameServer::DestroyReportThread(void)
{
	if (m_hReportThread) {
		CloseHandle(m_hReportThread);
		m_hReportThread = NULL;
	}
}

//
// 销毁更新线程
//
void CGameServer::DestroyUpdateThread(void)
{
	if (m_hUpdateThread) {
		CloseHandle(m_hUpdateThread);
		m_hUpdateThread = NULL;
	}
}

//
// 获得游戏
//
CGame* CGameServer::GetNextGame(void)
{
	return NULL;
}

//
// 释放游戏
//
void CGameServer::ReleaseGame(CGame *pGame)
{

}

//
// 查询玩家
//
CPlayer* CGameServer::QueryPlayer(DWORD guid)
{
	return NULL;
}

//
// 注册玩家
//
BOOL CGameServer::RegisterPlayer(CPlayer *pPlayer, DWORD guid)
{
	return TRUE;
}

//
// 注销玩家
//
BOOL CGameServer::UnRegisterPlayer(CPlayer *pPlayer)
{
	return TRUE;
}

//
// 发送指定玩家
//
void CGameServer::SendToPlayer(CPlayer *pPlayer, BYTE *pBuffer, DWORD size)
{

}

//
// 发送所有玩家
//
void CGameServer::SendToPlayerAll(CGame *pGame, CPlayer *pPlayerIgnore, BYTE *pBuffer, DWORD size, DWORD dwFilter)
{

}

//
// 客户端链接回调
//
void CGameServer::OnConnect(CIOContext *pIOContext, SOCKET acceptSocket)
{

}

//
// 客户端断链回调
//
void CGameServer::OnDisconnect(CIOContext *pIOContext)
{

}

//
// 更新接收消息
//
void CGameServer::OnUpdateRecv(DWORD dwDeltaTime)
{

}

//
// 更新发送消息
//
void CGameServer::OnUpdateSend(void)
{

}

//
// 更新游戏
//
void CGameServer::OnUpdateGame(float deltaTime)
{

}

//
// 心跳
//
void CGameServer::OnHeart(CPlayer *pPlayer)
{

}

//
// 重置心跳
//
void CGameServer::OnHeartReset(CPlayer *pPlayer)
{

}

//
// 登陆
//
void CGameServer::OnLogin(CPlayer *pPlayer)
{

}

//
// 设置标识
//
void CGameServer::OnFlags(CPlayer *pPlayer)
{

}

//
// 创建游戏
//
void CGameServer::OnCreateGame(CPlayer *pPlayer)
{

}

//
// 销毁游戏
//
void CGameServer::OnDestroyGame(CPlayer *pPlayer)
{

}

//
// 进入游戏
//
void CGameServer::OnEnterGame(CPlayer *pPlayer)
{

}

//
// 退出游戏
//
void CGameServer::OnExitGame(CPlayer *pPlayer)
{

}

//
// 发送指定玩家
//
void CGameServer::OnSendToPlayer(CPlayer *pPlayer, WORD packSize)
{

}

//
// 发送所有玩家
//
void CGameServer::OnSendToPlayerAll(CPlayer *pPlayer, WORD packSize)
{

}

//
// 发送所有玩家(带过滤)
//
void CGameServer::OnSendToPlayerFilterAll(CPlayer *pPlayer, WORD packSize)
{

}

//
// 监控
//
void CGameServer::Monitor(void)
{

}

//
// 报告
//
void CGameServer::Report(BYTE *buffer, CCacheBuffer *pCacheBuffer)
{

}

//
// 汇报线程
//
DWORD WINAPI CGameServer::ReportThread(LPVOID lpParam)
{
	return 0L;
}

//
// 更新线程
//
DWORD WINAPI CGameServer::UpdateThread(LPVOID lpParam)
{
	return 0L;
}
