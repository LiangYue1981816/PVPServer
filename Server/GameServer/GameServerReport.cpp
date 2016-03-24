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
			BYTE buffer[1024 * 1024];
			CCacheBuffer writeBuffer(sizeof(buffer), buffer);
			ProtoGameServer::ServerStatus requestServerStatus;
			{
				EnterCriticalSection(&pServer->m_sectionIOContext);
				{
					requestServerStatus.set_ip(pServer->m_ip);
					requestServerStatus.set_port(pServer->m_port);
					requestServerStatus.set_maxgames(pServer->m_maxGames);
					requestServerStatus.set_curgames(pServer->m_curGames);
				}
				LeaveCriticalSection(&pServer->m_sectionIOContext);
			}
			Serializer(&writeBuffer, &requestServerStatus, ProtoGameServer::REQUEST_MSG::SERVER_STATUS);

			rcode = SendData(sock, (char *)buffer, writeBuffer.GetActiveBufferSize());
			if (rcode < 0) goto RETRY;
		}

		if (sock != INVALID_SOCKET) {
			shutdown(sock, SD_BOTH);
			closesocket(sock);
			sock = INVALID_SOCKET;
		}
	}

	return 0L;
}
