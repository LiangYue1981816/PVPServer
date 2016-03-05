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
	OnExitGame((CPlayer *)pIOContext, 0);
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
					WORD fullSize = *(WORD *)pPlayer->recvBuffer.GetPopPointer();
					WORD bodySize = fullSize - sizeof(msg);

					if (pPlayer->recvBuffer.GetActiveBufferSize() < sizeof(fullSize) + fullSize) break;
					if (pPlayer->recvBuffer.PopData((BYTE *)&fullSize, sizeof(fullSize)) == FALSE) break;
					if (pPlayer->recvBuffer.PopData((BYTE *)&msg, sizeof(msg)) == FALSE)  break;

					m_dwRecvDataSize += sizeof(fullSize) + fullSize;

					switch (msg) {
					case Client::SERVER_MSG::HEART:
						OnHeart(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::LOGIN:
						OnLogin(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::FLAGS:
						OnFlags(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::CREATE_GAME:
						OnCreateGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::DESTROY_GAME:
						OnDestroyGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::ENTER_GAME:
						OnEnterGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::EXIT_GAME:
						OnExitGame(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::MODIFY_GAME_PASSWORD:
						OnModifyGamePassword(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::SEND_TO_PLAYER:
						OnSendToPlayer(pPlayer, bodySize);
						OnHeartReset(pPlayer);
						break;

					case Client::SERVER_MSG::SEND_TO_PLAYER_ALL:
						OnSendToPlayerAll(pPlayer, bodySize);
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
// 重置心跳
//
void CGameServer::OnHeartReset(CPlayer *pPlayer)
{

}

//
// 心跳
//
void CGameServer::OnHeart(CPlayer *pPlayer, WORD size)
{

}

//
// 登陆
//
void CGameServer::OnLogin(CPlayer *pPlayer, WORD size)
{

}

//
// 设置标识
//
void CGameServer::OnFlags(CPlayer *pPlayer, WORD size)
{

}

//
// 创建游戏
//
void CGameServer::OnCreateGame(CPlayer *pPlayer, WORD size)
{

}

//
// 销毁游戏
//
void CGameServer::OnDestroyGame(CPlayer *pPlayer, WORD size)
{

}

//
// 进入游戏
//
void CGameServer::OnEnterGame(CPlayer *pPlayer, WORD size)
{

}

//
// 退出游戏
//
void CGameServer::OnExitGame(CPlayer *pPlayer, WORD size)
{

}

//
// 修改游戏密码
//
void CGameServer::OnModifyGamePassword(CPlayer *pPlayer, WORD size)
{

}

//
// 发送指定玩家
//
void CGameServer::OnSendToPlayer(CPlayer *pPlayer, WORD size)
{

}

//
// 发送所有玩家
//
void CGameServer::OnSendToPlayerAll(CPlayer *pPlayer, WORD size)
{

}

