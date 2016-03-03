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
// 更新发送消息
//
void CGameServer::OnUpdateSend(void)
{
	if (CPlayer *pPlayer = (CPlayer *)m_pActiveContext) {
		do {
			if (pPlayer->IsAlive()) {
				pPlayer->sendBuffer.Lock();
				{
					pPlayer->OnSendNext(NULL, 0, 0);
				}
				pPlayer->sendBuffer.Unlock();
			}
		} while (pPlayer = (CPlayer *)pPlayer->pNextActive);
	}
}

//
// 更新接收消息
//
void CGameServer::OnUpdateRecv(DWORD dwDeltaTime)
{
	CPlayer *pPlayer = (CPlayer *)m_pActiveContext;

	while (pPlayer) {
		CPlayer *pNextPlayer = (CPlayer *)pPlayer->pNextActive;

		if (pPlayer->IsAlive()) {
			pPlayer->recvBuffer.Lock();
			{
				pPlayer->dwHeartTime += dwDeltaTime;

				while (TRUE) {
					WORD msg = 0;
					WORD size = *(WORD *)pPlayer->recvBuffer.GetPopPointer();

					if (pPlayer->recvBuffer.GetActiveBufferSize() < sizeof(size) + size) break;
					if (!pPlayer->recvBuffer.PopData((BYTE *)&size, sizeof(size))) break;
					if (!pPlayer->recvBuffer.PopData((BYTE *)&msg, sizeof(msg)))  break;

					m_dwRecvDataSize += size;

					switch (msg) {
					case GAMESERVER_MSG_C2S_HEART:
						OnHeart(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_LOGIN:
						OnLogin(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_FLAGS:
						OnFlags(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_CREATE_GAME:
						OnCreateGame(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_DESTROY_GAME:
						OnDestroyGame(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_ENTER_GAME:
						OnEnterGame(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_EXIT_GAME:
						OnExitGame(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_MODIFY_GAME_PASSWORD:
						OnModifyGamePassword(pPlayer);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_SENDTO_PLAYER:
						OnSendToPlayer(pPlayer, size);
						OnHeartReset(pPlayer);
						break;

					case GAMESERVER_MSG_C2S_SENDTO_PLAYER_ALL:
						OnSendToPlayerAll(pPlayer, size);
						OnHeartReset(pPlayer);
						break;

					default:
						OnUpdateGameMessage(pPlayer, msg);
						OnHeartReset(pPlayer);
						break;
					}
				}
			}
			pPlayer->recvBuffer.Unlock();
		}

		if (pPlayer->dwHeartTime > (DWORD)(1000 * m_timeOut)) {
			WriteLog("%s: Heart TimeOut\n", pPlayer->ip);
			ReleaseIOContext(pPlayer, FALSE);
		}

		pPlayer = pNextPlayer;
	}
}

//
// 更新游戏消息
//
void CGameServer::OnUpdateGameMessage(CPlayer *pPlayer, WORD msg)
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
// 修改游戏密码
//
void CGameServer::OnModifyGamePassword(CPlayer *pPlayer)
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
