#pragma once


#include "GameServer.h"


//
// 玩家
//
class _ServerExport CPVPServer;
class _ServerExport CGameLogic;
class _ServerExport CPlayerLogic : public CPlayer
{
	// 构造/析构函数
public:
	CPlayerLogic(CPVPServer *s);
	virtual ~CPlayerLogic(void);


	// 方法
public:


	// 属性
protected:
};

//
// 游戏
//
class _ServerExport CGameLogic : public CGame
{
	// 构造/析构函数
public:
	CGameLogic(CPVPServer *s);
	virtual ~CGameLogic(void);


	// 方法
public:
	virtual void Update(float deltaTime);                                                          // 更新


	// 属性
protected:
};

//
// 服务器
//
class _ServerExport CPVPServer : public CGameServer
{
	// 构造/析构函数
public:
	CPVPServer(void);
	virtual ~CPVPServer(void);


	// 方法
protected:
	virtual BOOL AllocGames(int maxGames);                                                         // 分配游戏
	virtual BOOL AllocPlayers(int maxPlayers);                                                     // 分配玩家

protected:
	virtual void OnUpdateGameMessage(CPlayer *pPlayer, WORD size, WORD msg);                       // 更新游戏消息
	virtual void OnUpdateGameLogic(float deltaTime);                                               // 更新游戏逻辑


	// 属性
protected:
};
