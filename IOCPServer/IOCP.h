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
		CIOContext *pIOContext;                                                                    // IO上下文
	} WSA_BUFFER;


	// 构造/析构函数
public:
	CIOContext(void);
	virtual ~CIOContext(void);


	// 方法
public:
	virtual void Accept(SOCKET sock);                                                              // 接收SOCKET
	virtual void ClearBuffer(void);                                                                // 清空缓冲

	virtual BOOL IsAlive(void);                                                                    // 活动判断

	virtual BOOL Send(BYTE *pBuffer, DWORD size, DWORD dwType = 0);                                // 发送
	virtual BOOL Recv(DWORD size, DWORD dwType = 0);                                               // 接收

	virtual void OnComplete(WSA_BUFFER *pIOBuffer, DWORD dwTransferred);                           // 完成回调函数
	virtual void OnAccept(void);                                                                   // 接收SOCKET回调函数
	virtual void OnDisconnect(void);                                                               // 断开回调函数
	virtual void OnRecvNext(BYTE *pBuffer, DWORD size, DWORD dwType);                              // 接收回调函数
	virtual void OnSendNext(BYTE *pBuffer, DWORD size, DWORD dwType);                              // 发送回调函数


	// 属性
public:
	char ip[16];                                                                                   // 客户端ip地址
	DWORD dwHeartTime;                                                                             // 心跳时间

public:
	DWORD id;                                                                                      // id
	DWORD guid;                                                                                    // guid

	BOOL bInUsed;                                                                                  // 使用中
	SOCKET acceptSocket;                                                                           // SOCKET

	WSA_BUFFER wsaRecvBuffer;                                                                      // 接收缓冲
	WSA_BUFFER wsaSendBuffer;                                                                      // 发送缓冲

	CCacheBuffer recvBuffer;                                                                       // 接收缓冲
	CCacheBuffer sendBuffer;                                                                       // 发送缓冲

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
	virtual BOOL Start(const char *ip, int port, int maxContexts = 1000);                          // 启动服务器
	virtual void Stop(void);                                                                       // 停止服务器

protected:
	virtual BOOL AllocContexts(int maxContexts);                                                   // 分配IO上下文
	virtual BOOL CreateIOCP(void);                                                                 // 创建完成端口
	virtual BOOL CreateWorkThreads(void);                                                          // 创建工作线程
	virtual BOOL CreateListenThread(void);                                                         // 创建侦听线程
	virtual BOOL CreateShutdownEvent(void);                                                        // 创建关闭事件

	virtual void FreeContexts(void);                                                               // 释放IO上下文
	virtual void DestroyIOCP(void);                                                                // 销毁完成端口
	virtual void DestroyWorkThreads(void);                                                         // 销毁工作线程
	virtual void DestroyListenThread(void);                                                        // 销毁侦听线程
	virtual void DestroyShutdownEvent(void);                                                       // 销毁关闭事件

	virtual BOOL Listen(const char *ip, int port);                                                 // 侦听
	virtual void Disconnect(void);                                                                 // 断开连接

protected:
	virtual CIOContext* GetIOContext(BOOL bLock = TRUE);                                           // 获得IO上下文
	virtual CIOContext* GetIOContextByIndex(int index, BOOL bLock = TRUE);                         // 获得IO上下文
	virtual void ReleaseIOContext(CIOContext *pIOContext, BOOL bLock = TRUE);                      // 释放IO上下文

protected:
	virtual void OnConnect(CIOContext *pIOContext, SOCKET acceptSocket);                           // 客户端链接回调
	virtual void OnDisconnect(CIOContext *pIOContext);                                             // 客户端断链回调

protected:
	static DWORD WINAPI ListenThread(LPVOID lpParam);                                              // 监听线程
	static DWORD WINAPI WorkThread(LPVOID lpParam);                                                // 工作线程


	// 属性
protected:
	int m_port;                                                                                    // 端口
	char m_ip[16];                                                                                 // IP

protected:
	SOCKET m_listenSocket;                                                                         // 监听SOCKET

	HANDLE m_hIOCP;                                                                                // 完成端口句柄
	HANDLE m_hListenThread;                                                                        // 监听线程句柄
	HANDLE m_hWorkThreads[MAX_THREAD_COUNT];                                                       // 工作线程句柄

	HANDLE m_hShutdownEvent;                                                                       // 退出事件
	CRITICAL_SECTION m_sectionIOContext;                                                           // IO上下文临界区

	int m_curContexts;                                                                             // 当前IO上下文数
	int m_maxContexts;                                                                             // 最大IO上下文数
	CIOContext **m_contexts;                                                                       // IO上下文集合
	CIOContext *m_pFreeContext;                                                                    // 空闲IO上下文
	CIOContext *m_pActiveContext;                                                                  // 活动IO上下文
};

extern int GetProcessors(void);                                                                    // 获得处理器数
extern UINT tick(void);                                                                            // 始终滴答

extern int SendData(int s, char *buff, int n);                                                     // 发送数据
extern int RecvData(int s, char *buff, int n);                                                     // 接收数据
