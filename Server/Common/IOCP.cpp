#include "iocp.h"


//////////////////////////////////////////////////////////////////////////
// 上下文
//========================================================================
CIOContext::CIOContext(void)
	: dwHeartTime(0x00000000)

	, id(0xffffffff)
	, guid(0xffffffff)
	, dwUserData(0xffffffff)

	, m_bInUsed(FALSE)
	, m_acceptSocket(INVALID_SOCKET)

	, m_indexRecvBuffer(0)
	, m_indexSendBuffer(0)
	, m_bIsRecvBufferOverflow(FALSE)
	, m_bIsSendBufferOverflow(FALSE)

	, pNext(NULL)
	, pNextActive(NULL)
	, pPrevActive(NULL)
{
	m_recvBuffer[0].AllocBuffer(RECV_BUFFER_SIZE, NULL);
	m_recvBuffer[1].AllocBuffer(RECV_BUFFER_SIZE, NULL);
	m_sendBuffer[0].AllocBuffer(SEND_BUFFER_SIZE, NULL);
	m_sendBuffer[1].AllocBuffer(SEND_BUFFER_SIZE, NULL);

	InitializeCriticalSectionAndSpinCount(&m_sectionRecvBuffer, 4000);
	InitializeCriticalSectionAndSpinCount(&m_sectionSendBuffer, 4000);

	ClearBuffer();
}

CIOContext::~CIOContext(void)
{
	OnDisconnect();

	DeleteCriticalSection(&m_sectionRecvBuffer);
	DeleteCriticalSection(&m_sectionSendBuffer);
}

//
// 活动判断
//
BOOL CIOContext::IsAlive(void)
{
	return m_acceptSocket != INVALID_SOCKET ? TRUE : FALSE;
}

//
// 清空缓冲
//
void CIOContext::ClearBuffer(void)
{
	memset(ip, 0, sizeof(ip));

	memset(&m_wsaRecvBuffer, 0, sizeof(m_wsaRecvBuffer));
	memset(&m_wsaSendBuffer, 0, sizeof(m_wsaSendBuffer));

	m_wsaRecvBuffer.pContext = this;
	m_wsaSendBuffer.pContext = this;

	m_bIsRecvBufferOverflow = FALSE;
	m_bIsSendBufferOverflow = FALSE;

	m_recvBuffer[0].ClearBuffer();
	m_recvBuffer[1].ClearBuffer();
	m_sendBuffer[0].ClearBuffer();
	m_sendBuffer[1].ClearBuffer();
}

//
// 切换接收缓冲
//
void CIOContext::SwitchRecvBuffer(void)
{
	EnterCriticalSection(&m_sectionRecvBuffer);
	{
		if (m_recvBuffer[m_indexRecvBuffer].GetActiveBufferSize() == 0) {
			m_indexRecvBuffer = 1 - m_indexRecvBuffer;
		}
	}
	LeaveCriticalSection(&m_sectionRecvBuffer);
}

//
// 切换发送缓冲
//
void CIOContext::SwitchSendBuffer(void)
{
	EnterCriticalSection(&m_sectionSendBuffer);
	{
		if (m_sendBuffer[1 - m_indexSendBuffer].GetActiveBufferSize() == 0) {
			m_indexSendBuffer = 1 - m_indexSendBuffer;
		}
	}
	LeaveCriticalSection(&m_sectionSendBuffer);
}

//
// 获得接收缓冲
//
CCacheBuffer& CIOContext::GetRecvBuffer(void)
{
	return m_recvBuffer[m_indexRecvBuffer];
}

//
// 获得发送缓冲
//
CCacheBuffer& CIOContext::GetSendBuffer(void)
{
	return m_sendBuffer[m_indexSendBuffer];
}

//
// 发送数据
//
void CIOContext::Send(BYTE *pBuffer, DWORD size)
{
	if (m_bIsSendBufferOverflow == FALSE) {
		if (GetSendBuffer().PushData(pBuffer, size) != size) {
			m_bIsSendBufferOverflow = TRUE;
		}
	}
}

//
// 检查
//
BOOL CIOContext::Check(DWORD dwTimeOut)
{
	if (m_bIsRecvBufferOverflow || m_bIsSendBufferOverflow || dwHeartTime > dwTimeOut) {
		if (m_bIsRecvBufferOverflow) {
			WriteLog("%s: Recv buffer overflow\n", ip);
		}

		if (m_bIsSendBufferOverflow) {
			WriteLog("%s: Send buffer overflow\n", ip);
		}

		if (dwHeartTime > dwTimeOut) {
			WriteLog("%s: Heart TimeOut\n", ip);
		}

		return FALSE;
	}

	return TRUE;
}

//
// 接收SOCKET回调函数
//
void CIOContext::OnAccept(SOCKET sock)
{
	//
	// 1. 保存地址
	//
	SOCKADDR_IN addr;
	int size = sizeof(addr);
	memset(&addr, 0, sizeof(addr));

	m_acceptSocket = sock;
	getpeername(m_acceptSocket, (SOCKADDR *)&addr, &size);
	strcpy(ip, inet_ntoa(addr.sin_addr));

	//
	// 2. 设置Socket
	//
	int on = 1;
	int off = 0;
	setsockopt(m_acceptSocket, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(on));

	//
	// 3. 接收数据
	//
	WSARecv(2, RECV_LEN);
}

//
// 断开回调函数
//
void CIOContext::OnDisconnect(void)
{
	if (m_acceptSocket != INVALID_SOCKET) {
		shutdown(m_acceptSocket, SD_BOTH);
		closesocket(m_acceptSocket);
		m_acceptSocket = INVALID_SOCKET;
	}
}

//
// 完成回调函数
//
void CIOContext::OnComplete(WSA_BUFFER *pIOBuffer, DWORD dwTransferred)
{
	DWORD dwBytes = 0;
	DWORD dwFlags = 0;

	switch (pIOBuffer->operationType >> 16) {
	case RECV_POSTED:
		pIOBuffer->dwCompleteSize += dwTransferred;

		if (pIOBuffer->dwCompleteSize < pIOBuffer->dwRequestSize) {
			pIOBuffer->wsaBuffer.len = pIOBuffer->dwRequestSize - pIOBuffer->dwCompleteSize;
			pIOBuffer->wsaBuffer.buf = (char *)&pIOBuffer->dataBuffer[pIOBuffer->dwCompleteSize];
			::WSARecv(m_acceptSocket, &pIOBuffer->wsaBuffer, 1, &dwBytes, &dwFlags, &pIOBuffer->overlapped, NULL);
		}
		else {
			OnRecvNext(pIOBuffer->dataBuffer, pIOBuffer->dwCompleteSize, pIOBuffer->operationType & 0x0000ffff);
		}

		break;

	case SEND_POSTED:
		pIOBuffer->dwCompleteSize += dwTransferred;

		if (pIOBuffer->dwCompleteSize < pIOBuffer->dwRequestSize) {
			pIOBuffer->wsaBuffer.len = pIOBuffer->dwRequestSize - pIOBuffer->dwCompleteSize;
			pIOBuffer->wsaBuffer.buf = (char *)&pIOBuffer->dataBuffer[pIOBuffer->dwCompleteSize];
			::WSASend(m_acceptSocket, &pIOBuffer->wsaBuffer, 1, &dwBytes, dwFlags, &pIOBuffer->overlapped, NULL);
		}
		else {
			OnSendNext();
		}

		break;
	}
}

//
// 接收回调函数
//
void CIOContext::OnRecvNext(BYTE *pBuffer, DWORD size, DWORD dwType)
{
	EnterCriticalSection(&m_sectionRecvBuffer);
	{
		if (m_wsaRecvBuffer.dwCompleteSize == m_wsaRecvBuffer.dwRequestSize) {
			if (m_bIsRecvBufferOverflow == FALSE) {
				WORD wPackSize;

				switch (dwType) {
				case RECV_LEN:
					WSARecv(*(WORD *)pBuffer, RECV_DATA);
					break;

				case RECV_DATA:
					wPackSize = (WORD)size;

					if (m_recvBuffer[1 - m_indexRecvBuffer].PushData((BYTE *)&wPackSize, sizeof(wPackSize)) != sizeof(wPackSize)) {
						m_bIsRecvBufferOverflow = TRUE;
						break;
					}

					if (m_recvBuffer[1 - m_indexRecvBuffer].PushData(pBuffer, size) != size) {
						m_bIsRecvBufferOverflow = TRUE;
						break;
					}

					WSARecv(2, RECV_LEN);
					break;
				}
			}
		}
	}
	LeaveCriticalSection(&m_sectionRecvBuffer);
}

//
// 发送回调函数
//
void CIOContext::OnSendNext(void)
{
	EnterCriticalSection(&m_sectionSendBuffer);
	{
		if (m_wsaSendBuffer.dwCompleteSize == m_wsaSendBuffer.dwRequestSize) {
			if (m_bIsSendBufferOverflow == FALSE) {
				BYTE buffer[PACK_BUFFER_SIZE];
				size_t size = min(sizeof(buffer), m_sendBuffer[1 - m_indexSendBuffer].GetActiveBufferSize());

				if (size > 0) {
					if (m_sendBuffer[1 - m_indexSendBuffer].PopData(buffer, size) == size) {
						WSASend(buffer, size);
					}
				}
			}
		}
	}
	LeaveCriticalSection(&m_sectionSendBuffer);
}

//
// 接收
//
BOOL CIOContext::WSARecv(DWORD size, DWORD dwType)
{
	//
	// 1. 接收数据大小检查
	//
	if (size == 0) {
		return FALSE;
	}

	if (size > sizeof(m_wsaRecvBuffer.dataBuffer)) {
		m_bIsRecvBufferOverflow = TRUE;
		return FALSE;
	}

	//
	// 2. 投递接收操作
	//
	DWORD dwBytes = 0;
	DWORD dwFlags = 0;

	m_wsaRecvBuffer.dwRequestSize = size;
	m_wsaRecvBuffer.dwCompleteSize = 0;

	m_wsaRecvBuffer.wsaBuffer.len = size;
	m_wsaRecvBuffer.wsaBuffer.buf = (char *)m_wsaRecvBuffer.dataBuffer;
	m_wsaRecvBuffer.operationType = RECV_POSTED << 16 | dwType;

	::WSARecv(m_acceptSocket, &m_wsaRecvBuffer.wsaBuffer, 1, &dwBytes, &dwFlags, &m_wsaRecvBuffer.overlapped, NULL);

	return TRUE;
}

//
// 发送
//
BOOL CIOContext::WSASend(BYTE *pBuffer, DWORD size, DWORD dwType)
{
	//
	// 1. 发送数据大小检查
	//
	if (size == 0) {
		return FALSE;
	}

	if (size > sizeof(m_wsaSendBuffer.dataBuffer)) {
		m_bIsSendBufferOverflow = TRUE;
		return FALSE;
	}

	//
	// 2. 投递发送操作
	//
	DWORD dwBytes = 0;
	DWORD dwFlags = 0;

	memcpy(m_wsaSendBuffer.dataBuffer, pBuffer, size);

	m_wsaSendBuffer.dwRequestSize = size;
	m_wsaSendBuffer.dwCompleteSize = 0;

	m_wsaSendBuffer.wsaBuffer.len = size;
	m_wsaSendBuffer.wsaBuffer.buf = (char *)m_wsaSendBuffer.dataBuffer;
	m_wsaSendBuffer.operationType = SEND_POSTED << 16 | dwType;

	::WSASend(m_acceptSocket, &m_wsaSendBuffer.wsaBuffer, 1, &dwBytes, dwFlags, &m_wsaSendBuffer.overlapped, NULL);

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// IOCP Server
//========================================================================
CIOCPServer::CIOCPServer(void)
	: m_timeOut(5)
	, m_listenSocket(INVALID_SOCKET)

	, m_hIOCP(NULL)
	, m_hListenThread(NULL)
	, m_hShutdownEvent(NULL)

	, m_curContexts(0)
	, m_maxContexts(0)
	, m_contexts(NULL)
	, m_pFreeContext(NULL)
	, m_pActiveContext(NULL)
{
	m_port = 0;
	memset(m_ip, 0, sizeof(m_ip));
	memset(m_hTransferThreads, 0, sizeof(m_hTransferThreads));

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	InitializeCriticalSectionAndSpinCount(&m_sectionContext, 4000);
}

CIOCPServer::~CIOCPServer(void)
{
	WSACleanup();
	DeleteCriticalSection(&m_sectionContext);
}

//
// 启动
//
BOOL CIOCPServer::Start(const char *ip, int port, int maxContexts, int timeOut)
{
	m_timeOut = max(5, timeOut);

	if (AllocContexts(maxContexts) == FALSE) return FALSE;
	if (Listen(ip, port) == FALSE) return FALSE;
	if (CreateIOCP() == FALSE) return FALSE;
	if (CreateShutdownEvent() == FALSE) return FALSE;
	if (CreateListenThread() == FALSE) return FALSE;
	if (CreateTransferThreads() == FALSE) return FALSE;

	return TRUE;
}

//
// 停止
//
void CIOCPServer::Stop(void)
{
	SetEvent(m_hShutdownEvent);

	Disconnect();
	DestroyIOCP();
	DestroyListenThread();
	DestroyTransferThreads();
	DestroyShutdownEvent();
	FreeContexts();
}

//
// 分配上下文
//
BOOL CIOCPServer::AllocContexts(int maxContexts)
{
	//
	// 1. 分配上下文存储
	//
	m_curContexts = 0;
	m_maxContexts = maxContexts;
	m_contexts = new CIOContext*[m_maxContexts];

	//
	// 2. 建立空闲上下文链表
	//
	for (int indexContext = 0; indexContext < m_maxContexts; indexContext++) {
		m_contexts[indexContext] = new CIOContext;
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
// 创建IOCP
//
BOOL CIOCPServer::CreateIOCP(void)
{
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	return m_hIOCP != NULL ? TRUE : FALSE;
}

//
// 创建侦听线程
//
BOOL CIOCPServer::CreateListenThread(void)
{
	m_hListenThread = CreateThread(0, 0, ListenThread, (LPVOID)this, 0, NULL);
	return m_hListenThread != NULL ? TRUE : FALSE;
}

//
// 创建传输线程
//
BOOL CIOCPServer::CreateTransferThreads(void)
{
	int numThreads = GetProcessors() * 2 + 1;

	for (int indexThread = 0; indexThread < min(numThreads, MAX_THREAD_COUNT); indexThread++) {
		m_hTransferThreads[indexThread] = CreateThread(0, 0, TransferThread, (LPVOID)this, 0, NULL);
		if (m_hTransferThreads[indexThread] == NULL) return FALSE;
	}

	return TRUE;
}

//
// 创建关闭事件
//
BOOL CIOCPServer::CreateShutdownEvent(void)
{
	m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	return m_hShutdownEvent != NULL ? TRUE : FALSE;
}

//
// 释放上下文
//
void CIOCPServer::FreeContexts(void)
{
	if (m_contexts) {
		for (int indexContext = 0; indexContext < m_maxContexts; indexContext++) {
			delete m_contexts[indexContext];
		}

		delete[] m_contexts;
	}

	m_curContexts = 0;
	m_maxContexts = 0;

	m_contexts = NULL;
	m_pFreeContext = NULL;
	m_pActiveContext = NULL;
}

//
// 销毁IOCP
//
void CIOCPServer::DestroyIOCP(void)
{
	if (m_hIOCP) {
		CloseHandle(m_hIOCP);
		m_hIOCP = NULL;
	}
}

//
// 销毁侦听线程
//
void CIOCPServer::DestroyListenThread(void)
{
	if (m_hListenThread) {
		WaitForSingleObject(m_hListenThread, INFINITE);
		CloseHandle(m_hListenThread);
		m_hListenThread = NULL;
	}
}

//
// 销毁传输线程
//
void CIOCPServer::DestroyTransferThreads(void)
{
	int numThreads = GetProcessors() * 2 + 1;

	PostQueuedCompletionStatus(m_hIOCP, 0, 0, NULL);
	WaitForMultipleObjects(min(numThreads, MAX_THREAD_COUNT), m_hTransferThreads, TRUE, INFINITE);

	for (int indexThread = 0; indexThread < min(numThreads, MAX_THREAD_COUNT); indexThread++) {
		if (m_hTransferThreads[indexThread]) {
			CloseHandle(m_hTransferThreads[indexThread]);
			m_hTransferThreads[indexThread] = NULL;
		}
	}
}

//
// 销毁关闭事件
//
void CIOCPServer::DestroyShutdownEvent(void)
{
	if (m_hShutdownEvent) {
		CloseHandle(m_hShutdownEvent);
		m_hShutdownEvent = NULL;
	}
}

//
// 监听
//
BOOL CIOCPServer::Listen(const char *ip, int port)
{
	//
	// 1. 创建SOCKET
	//
	SOCKADDR_IN serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(ip);
	serverAddress.sin_port = htons(port);

	m_listenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (m_listenSocket == INVALID_SOCKET) return FALSE;

	//
	// 2. 绑定并开始监听
	//
	bind(m_listenSocket, (PSOCKADDR)&serverAddress, sizeof(serverAddress));
	if (WSAGetLastError() != NO_ERROR) return FALSE;

	listen(m_listenSocket, SOMAXCONN);
	if (WSAGetLastError() != NO_ERROR) return FALSE;

	//
	// 3. 保存地址
	//
	m_port = port;
	strcpy(m_ip, ip);

	return TRUE;
}

//
// 断开连接
//
void CIOCPServer::Disconnect(void)
{
	if (m_listenSocket != INVALID_SOCKET) {
		shutdown(m_listenSocket, SD_BOTH);
		closesocket(m_listenSocket);
		m_listenSocket = INVALID_SOCKET;
	}
}

//
// 获得空闲上下文
//
CIOContext* CIOCPServer::GetNextContext(BOOL bLock)
{
	CIOContext *pContext = NULL;

	if (bLock) EnterCriticalSection(&m_sectionContext);
	{
		if (m_pFreeContext) {
			//
			// 1. 建立活动链表
			//
			pContext = m_pFreeContext;

			pContext->m_bInUsed = TRUE;
			pContext->pPrevActive = NULL;
			pContext->pNextActive = m_pActiveContext;

			if (m_pActiveContext) {
				m_pActiveContext->pPrevActive = pContext;
			}

			m_pActiveContext = pContext;

			//
			// 2. 建立空闲链表
			//
			m_pFreeContext = m_pFreeContext->pNext;

			//
			// 3. 记录上下文数
			//
			m_curContexts++;
		}
	}
	if (bLock) LeaveCriticalSection(&m_sectionContext);

	return pContext;
}

//
// 释放上下文
//
void CIOCPServer::ReleaseContext(CIOContext *pContext, BOOL bLock)
{
	if (bLock) EnterCriticalSection(&m_sectionContext);
	{
		if (pContext->m_bInUsed) {
			pContext->m_bInUsed = FALSE;

			//
			// 1. 断开连接
			//
			OnDisconnect(pContext);

			//
			// 2. 建立空闲链表
			//
			pContext->pNext = m_pFreeContext;
			m_pFreeContext = pContext;

			//
			// 3. 建立活动链表
			//
			if (pContext->pPrevActive) {
				pContext->pPrevActive->pNextActive = pContext->pNextActive;
			}

			if (pContext->pNextActive) {
				pContext->pNextActive->pPrevActive = pContext->pPrevActive;
			}

			if (m_pActiveContext == pContext) {
				m_pActiveContext = pContext->pNextActive;
			}

			pContext->pNextActive = NULL;
			pContext->pPrevActive = NULL;

			//
			// 3. 记录上下文数
			//
			m_curContexts--;
		}
	}
	if (bLock) LeaveCriticalSection(&m_sectionContext);
}

//
// 链接
//
void CIOCPServer::OnConnect(CIOContext *pContext, SOCKET acceptSocket)
{
	pContext->guid = 0xffffffff;
	pContext->dwUserData = 0xffffffff;
	pContext->dwHeartTime = 0x00000000;

	pContext->ClearBuffer();
	pContext->OnAccept(acceptSocket);
}

//
// 断连
//
void CIOCPServer::OnDisconnect(CIOContext *pContext)
{
	pContext->OnDisconnect();
}

//
// 更新发送
//
void CIOCPServer::OnUpdateSend(void)
{
	if (CIOContext *pContext = m_pActiveContext) {
		do {
			if (pContext->IsAlive()) {
				pContext->SwitchSendBuffer();
				pContext->OnSendNext();
			}
		} while (pContext = pContext->pNextActive);
	}
}

//
// 监听线程
//
DWORD WINAPI CIOCPServer::ListenThread(LPVOID lpParam)
{
	if (CIOCPServer *pIOCPServer = (CIOCPServer *)lpParam) {
		while (WAIT_OBJECT_0 != WaitForSingleObject(pIOCPServer->m_hShutdownEvent, 0)) {
			SOCKET acceptSocket = WSAAccept(pIOCPServer->m_listenSocket, NULL, NULL, NULL, 0);
			if (acceptSocket == INVALID_SOCKET) break;

			if (CIOContext *pContext = pIOCPServer->GetNextContext(TRUE)) {
				CreateIoCompletionPort((HANDLE)acceptSocket, pIOCPServer->m_hIOCP, (ULONG_PTR)acceptSocket, 0);
				pIOCPServer->OnConnect(pContext, acceptSocket);
			}
			else {
				shutdown(acceptSocket, SD_BOTH);
				closesocket(acceptSocket);
			}
		}
	}

	return 0L;
}

//
// 传输线程
//
DWORD WINAPI CIOCPServer::TransferThread(LPVOID lpParam)
{
	if (CIOCPServer *pIOCPServer = (CIOCPServer *)lpParam) {
		while (WAIT_OBJECT_0 != WaitForSingleObject(pIOCPServer->m_hShutdownEvent, 0)) {
			BOOL rcode = FALSE;
			DWORD dwTransferred = 0;
			SOCKET acceptSocket = INVALID_SOCKET;
			OVERLAPPED *pOverlapped = NULL;
			CIOContext::WSA_BUFFER *pIOBuffer = NULL;

			//
			// 1. 查询完成端口
			//
			rcode = GetQueuedCompletionStatus(pIOCPServer->m_hIOCP, &dwTransferred, (PULONG_PTR)&acceptSocket, (LPOVERLAPPED *)&pOverlapped, INFINITE);
			if (pOverlapped == NULL) continue;

			//
			// 2. 获得上下文
			//
			pIOBuffer = CONTAINING_RECORD(pOverlapped, CIOContext::WSA_BUFFER, overlapped);

			//
			// 3. 完成操作
			//
			if (rcode && dwTransferred) {
				pIOBuffer->pContext->OnComplete(pIOBuffer, dwTransferred);
				continue;
			}

			//
			// 4. 客户端断线, 回收上下文
			//
			pIOCPServer->ReleaseContext(pIOBuffer->pContext, TRUE);
		}
	}

	return 0L;
}


//////////////////////////////////////////////////////////////////////////
// 功能函数
//========================================================================
//
// 始终滴答
//
_ServerExport UINT tick(void)
{
	LARGE_INTEGER freq;
	LARGE_INTEGER count;

	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&count);

	return (UINT)(((double)count.QuadPart / freq.QuadPart) * 1000000);
}

//
// 字符串哈希值
//
_ServerExport DWORD HashValue(const char *szString)
{
	if (!szString) {
		return 0xffffffff;
	}

	DWORD dwHashValue = 0;
	const char *c = szString;

	while (*c) {
		dwHashValue = (dwHashValue << 5) - dwHashValue + (*c == '/' ? '\\' : *c);
		c++;
	}

	return dwHashValue;
}

//
// 获得处理器数
//
_ServerExport int GetProcessors(void)
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
}

//
// 发送数据
//
_ServerExport int SendData(int s, char *buff, int n)
{
	int bw = 0;
	int bcount = 0;

	while (bcount < n) {
		if ((bw = send(s, buff, n - bcount, 0)) > 0) {
			bcount += bw;
			buff += bw;
		}
		else {
			return SOCKET_ERROR;
		}
	}

	return bcount;
}

//
// 接收数据
//
_ServerExport int RecvData(int s, char *buff, int n)
{
	int br = 0;
	int bcount = 0;

	while (bcount < n) {
		if ((br = recv(s, buff, n - bcount, 0)) > 0) {
			bcount += br;
			buff += br;
		}
		else {
			return SOCKET_ERROR;
		}
	}

	return bcount;
}
