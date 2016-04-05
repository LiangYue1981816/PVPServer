#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#include "pthread.h"
#include "semaphore.h"
#include "Common.h"
#include "CacheBuffer.h"


class CIOContext
{
	friend class CIOCPServer;


	// 数据结构
public:
	enum {
		RECV_LEN = 0,                                                                              // 接收长度
		RECV_DATA                                                                                  // 接收数据
	};

	typedef enum {
		NONE_POSTED = 0,                                                                           // 无投递操作
		SEND_POSTED,                                                                               // 投递发送操作
		RECV_POSTED,                                                                               // 投递接收操作
	} OPERATION_TYPE;

	typedef struct {
		OVERLAPPED overlapped;                                                                     // 重叠结构

		WSABUF wsaBuffer;                                                                          // WSA缓冲
		BYTE dataBuffer[PACK_BUFFER_SIZE];                                                         // WSA指向的数据缓冲

		DWORD dwRequestSize;                                                                       // 请求数据大小
		DWORD dwCompleteSize;                                                                      // 完成数据大小

		DWORD operationType;                                                                       // 操作类型
		CIOContext *pContext;                                                                      // 上下文
	} WSA_BUFFER;


	// 构造/析构函数
public:
	CIOContext(void);
	virtual ~CIOContext(void);


	// 方法
public:
	virtual BOOL IsAlive(void);                                                                    // 活动判断
	virtual void ClearBuffer(void);                                                                // 清空缓冲
	virtual void Send(BYTE *pBuffer, DWORD size);                                                  // 发送数据
	virtual BOOL Check(DWORD dwTimeOut);                                                           // 检查

public:
	virtual void OnAccept(SOCKET sock);                                                            // 接收SOCKET回调函数
	virtual void OnDisconnect(void);                                                               // 断开回调函数
	virtual void OnComplete(WSA_BUFFER *pIOBuffer, DWORD dwTransferred);                           // 完成回调函数

protected:
	virtual void OnRecvNext(BYTE *pBuffer, DWORD size, DWORD dwType);                              // 接收回调函数
	virtual void OnSendNext(void);                                                                 // 发送回调函数

protected:
	virtual BOOL WSARecv(DWORD size, DWORD dwType = 0);                                            // 接收
	virtual BOOL WSASend(BYTE *pBuffer, DWORD size, DWORD dwType = 0);                             // 发送


	// 属性
public:
	char ip[256];                                                                                  // 客户端ip地址
	DWORD dwHeartTime;                                                                             // 心跳时间

public:
	DWORD id;                                                                                      // id
	DWORD guid;                                                                                    // guid

	BOOL bInUsed;                                                                                  // 使用中

	CCacheBuffer recvBuffer;                                                                       // 接收缓冲
	CCacheBuffer sendBuffer;                                                                       // 发送缓冲

protected:
	SOCKET acceptSocket;                                                                           // SOCKET

	WSA_BUFFER wsaRecvBuffer;                                                                      // 接收缓冲
	WSA_BUFFER wsaSendBuffer;                                                                      // 发送缓冲

protected:
	BOOL bIsRecvBufferOverflow;                                                                    // 接收缓冲溢出
	BOOL bIsSendBufferOverflow;                                                                    // 发送缓冲溢出

public:
	CIOContext *pNext;                                                                             // 下一个上下文
	CIOContext *pNextActive;                                                                       // 下一个上下文
	CIOContext *pPrevActive;                                                                       // 前一个上下文
};


class CIOCPServer
{
	static const int MAX_THREAD_COUNT = 128;


	// 构造/析构函数
public:
	CIOCPServer(void);
	virtual ~CIOCPServer(void);


	// 方法
public:
	virtual BOOL Start(const char *ip, int port, int maxContexts, int timeOut);                    // 启动服务器
	virtual void Stop(void);                                                                       // 停止服务器

protected:
	virtual BOOL AllocContexts(int maxContexts);                                                   // 分配上下文
	virtual BOOL CreateIOCP(void);                                                                 // 创建完成端口
	virtual BOOL CreateListenThread(void);                                                         // 创建侦听线程
	virtual BOOL CreateTransferThreads(void);                                                      // 创建传输线程
	virtual BOOL CreateShutdownEvent(void);                                                        // 创建关闭事件

	virtual void FreeContexts(void);                                                               // 释放上下文
	virtual void DestroyIOCP(void);                                                                // 销毁完成端口
	virtual void DestroyListenThread(void);                                                        // 销毁侦听线程
	virtual void DestroyTransferThreads(void);                                                     // 销毁传输线程
	virtual void DestroyShutdownEvent(void);                                                       // 销毁关闭事件

	virtual BOOL Listen(const char *ip, int port);                                                 // 侦听
	virtual void Disconnect(void);                                                                 // 断开连接

protected:
	virtual CIOContext* GetNextContext(BOOL bLock);                                                // 获得空闲上下文
	virtual void ReleaseContext(CIOContext *pContext, BOOL bLock);                                 // 释放上下文

protected:
	virtual void OnConnect(CIOContext *pContext, SOCKET acceptSocket);                             // 客户端链接回调
	virtual void OnDisconnect(CIOContext *pContext);                                               // 客户端断链回调

	virtual void OnUpdateSend(void);                                                               // 更新发送

protected:
	static DWORD WINAPI ListenThread(LPVOID lpParam);                                              // 监听线程
	static DWORD WINAPI TransferThread(LPVOID lpParam);                                            // 传输线程


	// 属性
protected:
	char m_ip[256];                                                                                // IP
	int m_port;                                                                                    // 端口
	int m_timeOut;                                                                                 // 心跳超时

protected:
	SOCKET m_listenSocket;                                                                         // 监听SOCKET

	HANDLE m_hIOCP;                                                                                // 完成端口句柄
	HANDLE m_hListenThread;                                                                        // 监听线程句柄
	HANDLE m_hTransferThreads[MAX_THREAD_COUNT];                                                   // 传输线程句柄

	HANDLE m_hShutdownEvent;                                                                       // 退出事件
	CRITICAL_SECTION m_sectionContext;                                                             // 上下文临界区

	int m_curContexts;                                                                             // 当前上下文数
	int m_maxContexts;                                                                             // 最大上下文数
	CIOContext **m_contexts;                                                                       // 上下文集合
	CIOContext *m_pFreeContext;                                                                    // 空闲上下文
	CIOContext *m_pActiveContext;                                                                  // 活动上下文
};

extern int GetProcessors(void);                                                                    // 获得处理器数
extern UINT tick(void);                                                                            // 始终滴答

extern int SendData(int s, char *buff, int n);                                                     // 发送数据
extern int RecvData(int s, char *buff, int n);                                                     // 接收数据

extern void WriteLog(const char *szFmt, ...);                                                      // 输出日志
