#include "GameServer.h"


CGameServer::CGameServer(void)
{

}

CGameServer::~CGameServer(void)
{

}

//
// 启动服务器
//
BOOL CGameServer::Start(const char *ip, int port, int maxGames, int maxPlayers, int timeOut, const char *rootip, int rootport)
{
	return TRUE;
}

//
// 停止服务器
//
void CGameServer::Stop(void)
{

}

//
// 分配玩家
//
BOOL CGameServer::AllocPlayers(int maxPlayers)
{
	return TRUE;
}

//
// 分配游戏
//
BOOL CGameServer::AllocGames(int maxGames)
{
	return TRUE;
}

//
// 创建汇报线程
//
BOOL CGameServer::CreateReportThread(void)
{
	return TRUE;
}

//
// 创建更新线程
//
BOOL CGameServer::CreateUpdateThread(void)
{
	return TRUE;
}

//
// 释放玩家
//
void CGameServer::FreePlayers(void)
{

}

//
// 释放游戏
//
void CGameServer::FreeGames(void)
{

}

//
// 销毁汇报线程
//
void CGameServer::DestroyReportThread(void)
{

}

//
// 销毁更新线程
//
void CGameServer::DestroyUpdateThread(void)
{

}

//
// 获得游戏
//
CGame* CGameServer::GetNextGame(void)
{
	return NULL;
}

//
// 释放游戏
//
void CGameServer::ReleaseGame(CGame *pGame)
{

}

//
// 查询玩家
//
CPlayer* CGameServer::QueryPlayer(DWORD guid)
{
	return NULL;
}

//
// 注册玩家
//
BOOL CGameServer::RegisterPlayer(CPlayer *pPlayer, DWORD guid)
{
	return TRUE;
}

//
// 注销玩家
//
BOOL CGameServer::UnRegisterPlayer(CPlayer *pPlayer)
{
	return TRUE;
}

//
// 发送指定玩家
//
void CGameServer::SendToPlayer(CPlayer *pPlayer, BYTE *pBuffer, DWORD size)
{

}

//
// 发送所有玩家
//
void CGameServer::SendToPlayerAll(CGame *pGame, CPlayer *pPlayerIgnore, BYTE *pBuffer, DWORD size, DWORD dwFilter)
{

}

//
// 客户端链接回调
//
void CGameServer::OnConnect(CIOContext *pIOContext, SOCKET acceptSocket)
{

}

//
// 客户端断链回调
//
void CGameServer::OnDisconnect(CIOContext *pIOContext)
{

}

//
// 更新接收消息
//
void CGameServer::OnUpdateRecv(DWORD dwDeltaTime)
{

}

//
// 更新发送消息
//
void CGameServer::OnUpdateSend(void)
{

}

//
// 更新游戏
//
void CGameServer::OnUpdateGame(float deltaTime)
{

}

//
// 心跳
//
void CGameServer::OnHeart(CPlayer *pPlayer)
{

}

//
// 重置心跳
//
void CGameServer::OnHeartReset(CPlayer *pPlayer)
{

}

//
// 登陆
//
void CGameServer::OnLogin(CPlayer *pPlayer)
{

}

//
// 设置标识
//
void CGameServer::OnFlags(CPlayer *pPlayer)
{

}

//
// 创建游戏
//
void CGameServer::OnCreateGame(CPlayer *pPlayer)
{

}

//
// 销毁游戏
//
void CGameServer::OnDestroyGame(CPlayer *pPlayer)
{

}

//
// 进入游戏
//
void CGameServer::OnEnterGame(CPlayer *pPlayer)
{

}

//
// 退出游戏
//
void CGameServer::OnExitGame(CPlayer *pPlayer)
{

}

//
// 发送指定玩家
//
void CGameServer::OnSendToPlayer(CPlayer *pPlayer, WORD packSize)
{

}

//
// 发送所有玩家
//
void CGameServer::OnSendToPlayerAll(CPlayer *pPlayer, WORD packSize)
{

}

//
// 发送所有玩家(带过滤)
//
void CGameServer::OnSendToPlayerFilterAll(CPlayer *pPlayer, WORD packSize)
{

}

//
// 监控
//
void CGameServer::Monitor(void)
{

}

//
// 报告
//
void CGameServer::Report(BYTE *buffer, CCacheBuffer *pCacheBuffer)
{

}

//
// 汇报线程
//
DWORD WINAPI CGameServer::ReportThread(LPVOID lpParam)
{
	return 0L;
}

//
// 更新线程
//
DWORD WINAPI CGameServer::UpdateThread(LPVOID lpParam)
{
	return 0L;
}
