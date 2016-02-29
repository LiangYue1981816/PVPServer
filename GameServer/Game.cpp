#include "GameServer.h"


CGame::CGame(CGameServer *s)
{

}

CGame::~CGame(void)
{

}

//
// 添加玩家
//
int CGame::AddPlayer(CPlayer *pPlayer, const char *password, BOOL bCreater)
{
	return 0;
}

//
// 删除玩家
//
int CGame::DelPlayer(CPlayer *pPlayer)
{
	return 0;
}

//
// 清空玩家
//
void CGame::Clear(void)
{

}

//
// 房间满判断
//
BOOL CGame::IsFull(void)
{
	return TRUE;
}

//
// 房间空判断
//
BOOL CGame::IsEmpty(void)
{
	return TRUE;
}

//
// 更新
//
void CGame::Update(float deltaTime)
{

}
