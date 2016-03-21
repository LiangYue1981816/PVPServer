#include "GameServer.h"


CPlayer::CPlayer(CGameServer *s)
	: pServer(s)
	, pGame(NULL)

	, m_dwFlags(0x00000000)

	, pNextPlayer(NULL)
	, pPrevPlayer(NULL)
{

}

CPlayer::~CPlayer(void)
{

}

//
// 设置标识
//
VOID CPlayer::SetFlags(DWORD dwFlags)
{
	m_dwFlags = dwFlags;
}

//
// 清空标识
//
VOID CPlayer::ClearFlags(void)
{
	m_dwFlags = 0x00000000;
}

//
// 使用标识
//
VOID CPlayer::EnableFlag(DWORD dwFlag)
{
	SET_ENABLE(m_dwFlags, dwFlag);
}

//
// 禁用标识
//
VOID CPlayer::DisableFlag(DWORD dwFlag)
{
	SET_DISABLE(m_dwFlags, dwFlag);
}

//
// 获得标识
//
DWORD CPlayer::GetFlags(void) const
{
	return m_dwFlags;
}

//
// 登陆状态
//
BOOL CPlayer::IsLogin(void) const
{
	return IS_ENABLE(m_dwFlags, ProtoGameServer::FLAGS_CODE::PLAYER_FLAGS_LOGIN);
}

//
// 已准备状态
//
BOOL CPlayer::IsReady(void) const
{
	return IS_ENABLE(m_dwFlags, ProtoGameServer::FLAGS_CODE::PLAYER_FLAGS_READY);
}

//
// 等待中状态
//
BOOL CPlayer::IsWaiting(void) const
{
	return IS_ENABLE(m_dwFlags, ProtoGameServer::FLAGS_CODE::PLAYER_FLAGS_WAITING);
}

//
// 游戏中状态
//
BOOL CPlayer::IsGaming(void) const
{
	return IS_ENABLE(m_dwFlags, ProtoGameServer::FLAGS_CODE::PLAYER_FLAGS_GAMING);
}
