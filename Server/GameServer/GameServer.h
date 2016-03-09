#pragma once


#include <map>
#include <vector>
#include <string>
#include "IOCP.h"
#include "Serializer.h"
#include "Flags.pb.h"
#include "Error.pb.h"
#include "Client.pb.h"
#include "Server.pb.h"
#include "Version.pb.h"


//
// 玩家
//
class CGame;
class CGameServer;
class CPlayer : public CIOContext
{
	// 构造/析构函数
public:
	CPlayer(CGameServer *s);
	virtual ~CPlayer(void);


	// 方法
public:
	virtual VOID SetFlags(DWORD dwFlags);                                                          // 设置标识
	virtual VOID ClearFlags(void);                                                                 // 清空标识

	virtual VOID EnableFlag(DWORD dwFlag);                                                         // 使用标识
	virtual VOID DisableFlag(DWORD dwFlag);                                                        // 禁用标识

	virtual DWORD GetFlags(void) const;                                                            // 获得标识

	virtual BOOL IsLogin(void) const;                                                              // 登陆状态
	virtual BOOL IsReady(void) const;                                                              // 已准备状态
	virtual BOOL IsWaiting(void) const;                                                            // 等待中状态
	virtual BOOL IsGaming(void) const;                                                             // 游戏中状态


	// 属性
private:
	DWORD m_dwFlags;                                                                               // 标识

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
	virtual void SetGame(const char *password, int mode, int mapid, int maxPlayers);               // 设置游戏

	virtual int GetMode(void) const;                                                               // 获得游戏模式
	virtual int GetMapID(void) const;                                                              // 获得游戏地图
	virtual int GetPlayers(void) const;                                                            // 获得当前玩家数
	virtual int GetMaxPlayers(void) const;                                                         // 获得最大玩家数

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
	DWORD id;                                                                                      // id

private:
	CHAR m_szPassword[16];                                                                         // 游戏密码

	int m_mode;                                                                                    // 游戏模式
	int m_mapid;                                                                                   // 游戏地图
	int m_maxPlayers;                                                                              // 最大玩家数
	int m_numPlayers;                                                                              // 当前玩家数

public:
	CGameServer *pServer;                                                                          // 服务器指针
	CPlayer *pActivePlayer;                                                                        // 玩家头指针

public:
	CGame *pNext;                                                                                  // 下一个游戏
	CGame *pNextActive;                                                                            // 下一个游戏
	CGame *pPrevActive;                                                                            // 前一个游戏
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
	virtual BOOL AllocGames(int maxGames);                                                         // 分配游戏
	virtual BOOL AllocPlayers(int maxPlayers);                                                     // 分配玩家
	virtual BOOL CreateReportThread(void);                                                         // 创建汇报线程
	virtual BOOL CreateUpdateThread(void);                                                         // 创建更新线程

	virtual void FreeGames(void);                                                                  // 释放游戏
	virtual void FreePlayers(void);                                                                // 释放玩家
	virtual void DestroyReportThread(void);                                                        // 销毁汇报线程
	virtual void DestroyUpdateThread(void);                                                        // 销毁更新线程

protected:
	virtual CGame* GetNextGame(void);                                                              // 获得游戏
	virtual void ReleaseGame(CGame *pGame);                                                        // 释放游戏

protected:
	virtual BOOL Login(CPlayer *pPlayer, DWORD guid);                                              // 玩家登陆
	virtual BOOL Logout(CPlayer *pPlayer);                                                         // 玩家注销
	virtual CPlayer* QueryPlayer(DWORD guid);                                                      // 查询玩家

protected:
	virtual void SendToPlayer(CPlayer *pPlayer, BYTE *pBuffer, size_t size);                       // 发送指定玩家
	virtual void SendToPlayerAll(CGame *pGame, CPlayer *pIgnore, BYTE *pBuffer, size_t size, DWORD dwFilter = 0xffffffff); // 发送所有玩家

protected:
	virtual void OnConnect(CIOContext *pIOContext, SOCKET acceptSocket);                           // 客户端链接回调
	virtual void OnDisconnect(CIOContext *pIOContext);                                             // 客户端断链回调

	virtual void OnUpdateSend(void);                                                               // 更新发送消息
	virtual void OnUpdateRecv(DWORD dwDeltaTime);                                                  // 更新接收消息
	virtual void OnUpdateGameMessage(CPlayer *pPlayer, WORD msg);                                  // 更新游戏消息
	virtual void OnUpdateGameLogic(float deltaTime);                                               // 更新游戏逻辑

	virtual void OnHeartReset(CPlayer *pPlayer);                                                   // 重置心跳
	virtual void OnHeart(CPlayer *pPlayer, WORD size);                                             // 心跳
	virtual void OnFlags(CPlayer *pPlayer, WORD size);                                             // 标识
	virtual void OnLogin(CPlayer *pPlayer, WORD size);                                             // 登陆
	virtual void OnCreateGame(CPlayer *pPlayer, WORD size);                                        // 创建游戏
	virtual void OnDestroyGame(CPlayer *pPlayer, WORD size);                                       // 销毁游戏
	virtual void OnEnterGame(CPlayer *pPlayer, WORD size);                                         // 进入游戏
	virtual void OnExitGame(CPlayer *pPlayer, WORD size);                                          // 退出游戏
	virtual void OnSendToPlayer(CPlayer *pPlayer, WORD size);                                      // 发送指定玩家
	virtual void OnSendToPlayerAll(CPlayer *pPlayer, WORD size);                                   // 发送所有玩家

protected:
	virtual void Monitor(void);                                                                    // 监控
	virtual void Report(BYTE *buffer, CCacheBuffer *pCacheBuffer);                                 // 报告

protected:
	static DWORD WINAPI ReportThread(LPVOID lpParam);                                              // 汇报线程
	static DWORD WINAPI UpdateThread(LPVOID lpParam);                                              // 更新线程


	// 属性
protected:
	GUIDMAP m_guidmap;                                                                             // 逻辑ID与连接ID映射表

protected:
	int m_curGames;                                                                                // 当前游戏数
	int m_maxGames;                                                                                // 最大游戏数
	CGame **m_games;                                                                               // 游戏集合
	CGame *m_pFreeGame;                                                                            // 空闲游戏
	CGame *m_pActiveGame;                                                                          // 活动游戏

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
