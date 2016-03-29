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
	GUIDMAP::const_iterator itContext = m_guidmap.find(guid);
	if (itContext != m_guidmap.end()) return FALSE;

	//
	// 3. 登陆
	//
	pContext->guid = guid;
	m_guidmap[guid] = pContext;

	return TRUE;
}

//
// 注销
//
BOOL CGateServer::Logout(CIOContext *pContext)
{
	//
	// 1. 查找
	//
	GUIDMAP::const_iterator itContext = m_guidmap.find(pContext->guid);
	if (itContext == m_guidmap.end()) return FALSE;

	//
	// 2. 注销
	//
	pContext->guid = 0xffffffff;
	m_guidmap.erase(itContext);

	return TRUE;
}

//
// 查询
//
CIOContext* CGateServer::QueryContext(DWORD guid)
{
	GUIDMAP::const_iterator itContext = m_guidmap.find(guid);
	return itContext != m_guidmap.end() ? itContext->second : NULL;
}

//
// 清理游戏服务器
//
void CGateServer::ClearGameServer(CIOContext *pContext)
{
	GameServerMap::const_iterator itGameServer = m_gameServerMap.find(pContext);
	if (itGameServer != m_gameServerMap.end()) m_gameServerMap.erase(itGameServer);
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
