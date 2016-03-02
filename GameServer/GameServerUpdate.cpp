#include "GameServer.h"


//
// 客户端链接回调
//
void CGameServer::OnConnect(CIOContext *pIOContext, SOCKET acceptSocket)
{
	((CPlayer *)pIOContext)->SetFlags(PLAYER_FLAGS_NONE);
	CIOCPServer::OnConnect(pIOContext, acceptSocket);
}

//
// 客户端断链回调
//
void CGameServer::OnDisconnect(CIOContext *pIOContext)
{
	OnExitGame((CPlayer *)pIOContext);
	UnRegisterPlayer((CPlayer *)pIOContext);

	CIOCPServer::OnDisconnect(pIOContext);
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
