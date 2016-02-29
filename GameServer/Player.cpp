#include "GameServer.h"


CPlayer::CPlayer(void)
{

}

CPlayer::~CPlayer(void)
{

}

//
// 登陆状态
//
BOOL CPlayer::IsLogin(void) const
{
	return TRUE;
}

//
// 已准备状态
//
BOOL CPlayer::IsReady(void) const
{
	return TRUE;
}

//
// 等待中状态
//
BOOL CPlayer::IsWaiting(void) const
{
	return TRUE;
}

//
// 游戏中状态
//
BOOL CPlayer::IsGaming(void) const
{
	return TRUE;
}
