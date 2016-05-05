#pragma once


#include "GameServer.h"


//
// 玩家
//
class _ServerExport CPVPGameServer;
class _ServerExport CPVPGame;
class _ServerExport CPVPPlayer : public CPlayer
{
	// 构造/析构函数
public:
	CPVPPlayer(CPVPGameServer *s);
	virtual ~CPVPPlayer(void);


	// 方法
public:


	// 属性
protected:
};

//
// 游戏
//
class _ServerExport CPVPGame : public CGame
{
	// 构造/析构函数
public:
	CPVPGame(CPVPGameServer *s);
	virtual ~CPVPGame(void);


	// 方法
public:
	virtual void Update(float deltaTime);                                                          // 更新


	// 属性
protected:
};

//
// 服务器
//
class _ServerExport CPVPGameServer : public CGameServer
{
	// 构造/析构函数
public:
	CPVPGameServer(void);
	virtual ~CPVPGameServer(void);


	// 方法
protected:
	virtual BOOL AllocGames(int maxGames);                                                         // 分配游戏
	virtual BOOL AllocPlayers(int maxPlayers);                                                     // 分配玩家


	// 属性
protected:
};
