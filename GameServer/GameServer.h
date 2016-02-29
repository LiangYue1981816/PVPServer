#pragma once


#include <map>
#include <vector>
#include <string>
#include "IOCP.h"


//
// 玩家
//
class CGame;
class CGameServer;
class CPlayer : public CIOContext
{
	// 构造/析构函数
public:
	CPlayer(void);
	virtual ~CPlayer(void);


	// 方法
public:
	virtual BOOL IsLogin(void) const;                                                              // 登陆状态
	virtual BOOL IsReady(void) const;                                                              // 已准备状态
	virtual BOOL IsWaiting(void) const;                                                            // 等待中状态
	virtual BOOL IsGaming(void) const;                                                             // 游戏中状态


	// 属性
public:
	DWORD dwFlags;                                                                                 // 标识

public:
	CGame *pGame;                                                                                  // 游戏
	CGameServer *pServer;                                                                          // 服务器

public:
	CPlayer *pNextPlayer;                                                                          // 下一个玩家
	CPlayer *pPrevPlayer;                                                                          // 前一个玩家
};

//
// 游戏
//
class CGame
{
	// 构造/析构函数
public:
	CGame(CGameServer *s);
	virtual ~CGame(void);


	// 方法
public:
	virtual int AddPlayer(CPlayer *pPlayer, const char *password, BOOL bCreater);                  // 添加玩家
	virtual int DelPlayer(CPlayer *pPlayer);                                                       // 删除玩家

	virtual void Clear(void);                                                                      // 清空玩家

	virtual BOOL IsFull(void);                                                                     // 房间满判断
	virtual BOOL IsEmpty(void);                                                                    // 房间空判断

public:
	virtual void Update(float deltaTime);                                                          // 更新


	// 属性
public:
	CGameServer *pServer;                                                                          // 服务器指针
	CPlayer *pActivePlayer;                                                                        // 玩家头指针
};

//
// 服务器
//
class CGameServer : public CIOCPServer
{
	// 数据结构
public:
	typedef std::map<DWORD, int> GUIDMAP;                                                          // GUID映射表


	// 构造/析构函数
public:
	CGameServer(void);
	virtual ~CGameServer(void);


	// 方法
public:
	virtual BOOL Start(const char *ip, int port, int maxGames, int maxPlayers, int timeOut, const char *rootip, int rootport); // 启动服务器
	virtual void Stop(void);                                                                       // 停止服务器

protected:
	virtual BOOL AllocPlayers(int maxPlayers);                                                     // 分配玩家
	virtual BOOL AllocGames(int maxGames);                                                         // 分配游戏
	virtual BOOL CreateReportThread(void);                                                         // 创建汇报线程
	virtual BOOL CreateUpdateThread(void);                                                         // 创建更新线程

	virtual void FreePlayers(void);                                                                // 释放玩家
	virtual void FreeGames(void);                                                                  // 释放游戏
	virtual void DestroyReportThread(void);                                                        // 销毁汇报线程
	virtual void DestroyUpdateThread(void);                                                        // 销毁更新线程

protected:
	virtual CGame* GetNextGame(void);                                                              // 获得游戏
	virtual void ReleaseGame(CGame *pGame);                                                        // 释放游戏

protected:
	virtual CPlayer* QueryPlayer(DWORD guid);                                                      // 查询玩家
	virtual BOOL RegisterPlayer(CPlayer *pPlayer, DWORD guid);                                     // 注册玩家
	virtual BOOL UnRegisterPlayer(CPlayer *pPlayer);                                               // 注销玩家

protected:
	virtual void SendToPlayer(CPlayer *pPlayer, BYTE *pBuffer, DWORD size);                        // 发送指定玩家
	virtual void SendToPlayerAll(CGame *pGame, CPlayer *pPlayerIgnore, BYTE *pBuffer, DWORD size, DWORD dwFilter = 0xffffffff); // 发送所有玩家

protected:
	virtual void OnConnect(CIOContext *pIOContext, SOCKET acceptSocket);                           // 客户端链接回调
	virtual void OnDisconnect(CIOContext *pIOContext);                                             // 客户端断链回调

	virtual void OnUpdateRecv(DWORD dwDeltaTime);                                                  // 更新接收消息
	virtual void OnUpdateSend(void);                                                               // 更新发送消息
	virtual void OnUpdateGame(float deltaTime);                                                    // 更新游戏

	virtual void OnHeart(CPlayer *pPlayer);                                                        // 心跳
	virtual void OnHeartReset(CPlayer *pPlayer);                                                   // 重置心跳
	virtual void OnLogin(CPlayer *pPlayer);                                                        // 登陆
	virtual void OnFlags(CPlayer *pPlayer);                                                        // 设置标识
	virtual void OnCreateGame(CPlayer *pPlayer);                                                   // 创建游戏
	virtual void OnDestroyGame(CPlayer *pPlayer);                                                  // 销毁游戏
	virtual void OnEnterGame(CPlayer *pPlayer);                                                    // 进入游戏
	virtual void OnExitGame(CPlayer *pPlayer);                                                     // 退出游戏
	virtual void OnSendToPlayer(CPlayer *pPlayer, WORD packSize);                                  // 发送指定玩家
	virtual void OnSendToPlayerAll(CPlayer *pPlayer, WORD packSize);                               // 发送所有玩家
	virtual void OnSendToPlayerFilterAll(CPlayer *pPlayer, WORD packSize);                         // 发送所有玩家(带过滤)

protected:
	virtual void Monitor(void);                                                                    // 监控
	virtual void Report(BYTE *buffer, CCacheBuffer *pCacheBuffer);                                 // 报告

protected:
	static DWORD WINAPI ReportThread(LPVOID lpParam);                                              // 汇报线程
	static DWORD WINAPI UpdateThread(LPVOID lpParam);                                              // 更新线程


	// 属性
protected:
	GUIDMAP guidmap;                                                                               // 逻辑ID与连接ID映射表

protected:
	int m_maxGames;                                                                                // 游戏数
	CGame **m_games;                                                                               // 游戏集合

	int m_timeOut;                                                                                 // 心跳超时

	HANDLE m_hReportThread;                                                                        // 汇报线程句柄
	HANDLE m_hUpdateThread;                                                                        // 更新线程句柄

protected:
	int m_nRootServerPort;                                                                         // 入口服务器端口
	char m_szRootServerIP[16];                                                                     // 入口服务器IP

protected:
	DWORD m_dwUpdateCount;                                                                         // 更新次数
	DWORD m_dwUpdateTime;                                                                          // 平均更新时间
	DWORD m_dwUpdateTimeTotal;                                                                     // 更新总时间
	DWORD m_dwRuntimeTotal;                                                                        // 总运行时间

	DWORD m_dwRecvDataSize;                                                                        // 接收数据量
	DWORD m_dwSendDataSize;                                                                        // 发送数据量
};

extern void WriteLog(const char *szFmt, ...);                                                      // 输出日志