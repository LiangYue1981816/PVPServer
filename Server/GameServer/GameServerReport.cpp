#include "GameServer.h"


//
// 汇报线程
//
DWORD WINAPI CGameServer::ReportThread(LPVOID lpParam)
{
	if (CGameServer *pServer = (CGameServer *)lpParam) {
		SOCKET sock = INVALID_SOCKET;

	RETRY:
		if (sock != INVALID_SOCKET) {
			shutdown(sock, SD_BOTH);
			closesocket(sock);
			sock = INVALID_SOCKET;
		}

		while (WAIT_OBJECT_0 != WaitForSingleObject(pServer->m_hShutdownEvent, 0)) {
			Sleep(1000);
			int rcode = NO_ERROR;

			//
			// 1. 链接网关服务器
			//
			if (sock == INVALID_SOCKET) {
				sockaddr_in sockAddr;
				sockAddr.sin_family = AF_INET;
				sockAddr.sin_addr.s_addr = inet_addr(pServer->m_szGateServerIP);
				sockAddr.sin_port = htons(pServer->m_nGateServerPort);

				sock = socket(AF_INET, SOCK_STREAM, 0);
				if (sock == INVALID_SOCKET) goto RETRY;

				rcode = connect(sock, (const struct sockaddr *)&sockAddr, sizeof(sockAddr));
				if (rcode != NO_ERROR) goto RETRY;
			}

			//
			// 2. 向网关服务器报告当前游戏列表
			//
			static BYTE buffer[1024 * 1024];
			CCacheBuffer writeBuffer(sizeof(buffer), buffer);

			ProtoGameServer::GameList requestGameList;
			requestGameList.set_ip(pServer->m_ip);
			requestGameList.set_port(pServer->m_port);

			EnterCriticalSection(&pServer->m_sectionIOContext);
			{
				if (CGame *pGame = pServer->m_pActiveGame) {
					do {
						if (ProtoGameServer::GameList_Game *pRequestGame = requestGameList.add_games()) {
							pRequestGame->set_private_(pGame->IsPrivate() ? true : false);
							pRequestGame->set_gameid(pGame->id);
							pRequestGame->set_mode(pGame->GetMode());
							pRequestGame->set_map(pGame->GetMapID());
							pRequestGame->set_maxplayers(pGame->GetMaxPlayers());

							if (CPlayer *pPlayer = pGame->pActivePlayer) {
								do {
									pRequestGame->add_playes(pPlayer->guid);
								} while (pPlayer = pPlayer->pNextPlayer);
							}
						}
					} while (pGame = pGame->pNextActive);
				}
			}
			LeaveCriticalSection(&pServer->m_sectionIOContext);

			Serializer(&writeBuffer, &requestGameList, ProtoGameServer::REQUEST_MSG::GAME_LIST);

			rcode = SendData(sock, (char *)buffer, writeBuffer.GetActiveBufferSize());
			if (rcode != NO_ERROR) goto RETRY;
		}

		if (sock != INVALID_SOCKET) {
			shutdown(sock, SD_BOTH);
			closesocket(sock);
			sock = INVALID_SOCKET;
		}
	}

	return 0L;
}
