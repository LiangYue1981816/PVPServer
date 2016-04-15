#include "PVPGateServer.h"


//
// 更新匹配
//
void CPVPGateServer::OnUpdateMatch(DWORD dwDeltaTime)
{
	static DWORD dwTime = 0;
	static const float maxTimeOut = 100.0f;
	static const int maxMatchs = 6;
	static const int minEvaluation = 0;
	static const int maxEvaluation = 10000;

	ProtoGateServer::Match responseMatch;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 更新频率检查
	//
	dwTime += dwDeltaTime;

	if (dwTime < 1000) {
		return;
	}

	dwTime = 0;

	//
	// 2. 计算当前玩家匹配范围
	//    超时玩家发送匹配失败消息
	//
	for (PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.begin(); itPlayerMap != m_evaluations.end(); ++itPlayerMap) {
		for (std::map<DWORD, PlayerStatus>::iterator itPlayer = itPlayerMap->second.begin(); itPlayer != itPlayerMap->second.end(); ++itPlayer) {
			itPlayer->second.timeout += 1.0f;

			// 2.1. 计算匹配范围
			if (itPlayer->second.timeout < maxTimeOut) {
				itPlayer->second.minEvaluation = (int)(itPlayerMap->first - maxEvaluation * itPlayer->second.timeout / maxTimeOut + 0.5f);
				itPlayer->second.maxEvaluation = (int)(itPlayerMap->first + maxEvaluation * itPlayer->second.timeout / maxTimeOut + 0.5f);

				if (itPlayer->second.minEvaluation < minEvaluation) itPlayer->second.minEvaluation = minEvaluation;
				if (itPlayer->second.maxEvaluation > maxEvaluation) itPlayer->second.maxEvaluation = maxEvaluation;
			}
			// 2.2. 超时匹配失败
			else {
				// 2.2.1. 发送匹配失败消息
				responseMatch.set_err(ProtoGateServer::ERROR_CODE::ERR_MATCH_TIMEOUT);

				Serializer(&writeBuffer, &responseMatch, ProtoGateServer::RESPONSE_MSG::MATCH);
				SendTo(itPlayer->second.pContext, buffer, writeBuffer.GetActiveBufferSize());

				// 2.2.2. 从待匹配玩家集合中移除
				itPlayer = itPlayerMap->second.erase(itPlayer);

				if (itPlayerMap->second.empty()) {
					itPlayerMap = m_evaluations.erase(itPlayerMap);
				}
			}
		}
	}

	//
	// 3. 匹配计算
	//
	for (PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.begin(); itPlayerMap != m_evaluations.end(); ++itPlayerMap) {
		for (std::map<DWORD, PlayerStatus>::iterator itPlayer = itPlayerMap->second.begin(); itPlayer != itPlayerMap->second.end(); ++itPlayer) {
			CIOContext *matchs[maxMatchs] = { itPlayer->second.pContext };
			BOOL bMatch = FALSE;

			int numMatchs = 1;
			int evaluation = itPlayerMap->first;
			int evaluationOffset = (itPlayer->second.maxEvaluation - itPlayer->second.minEvaluation) / 2;

			// 3.1. 尝试匹配
			bMatch = FALSE;
			numMatchs = 1;

			for (int offset = 0; offset <= evaluationOffset; offset++) {
				if (offset == 0) {
					bMatch |= Match(evaluation, itPlayer->second, NULL, numMatchs, maxMatchs);
				}
				else {
					bMatch |= Match(evaluation - offset, itPlayer->second, NULL, numMatchs, maxMatchs);
					bMatch |= Match(evaluation + offset, itPlayer->second, NULL, numMatchs, maxMatchs);
				}
			}

			// 3.2. 匹配失败
			if (bMatch == FALSE) {
				continue;
			}

			// 3.3. 正式匹配
			bMatch = FALSE;
			numMatchs = 1;

			for (int offset = 0; offset <= evaluationOffset; offset++) {
				if (offset == 0) {
					bMatch |= Match(evaluation, itPlayer->second, matchs, numMatchs, maxMatchs);
				}
				else {
					bMatch |= Match(evaluation - offset, itPlayer->second, matchs, numMatchs, maxMatchs);
					bMatch |= Match(evaluation + offset, itPlayer->second, matchs, numMatchs, maxMatchs);
				}
			}

			// 3.4. 选择服务器
			CIOContext *pServer = NULL;
			float minFactor = FLT_MAX;

			for (GameServerMap::const_iterator itGameServer = m_servers.begin(); itGameServer != m_servers.end(); ++itGameServer) {
				if (itGameServer->second.games.empty() == false) {
					float factor = 1.0f * itGameServer->second.curGames / itGameServer->second.maxGames;

					if (minFactor > factor) {
						minFactor = factor;
						pServer = itGameServer->first;
					}
				}
			}

			// 3.5. 发送房间信息
			if (pServer) {
				// 3.5.1. 发送房间信息
				responseMatch.set_err(ProtoGateServer::ERROR_CODE::ERR_NONE);
				responseMatch.set_ip(m_servers[pServer].ip);
				responseMatch.set_port(m_servers[pServer].port);
				responseMatch.set_gameid(m_servers[pServer].games[0].id);

				Serializer(&writeBuffer, &responseMatch, ProtoGateServer::RESPONSE_MSG::MATCH);

				for (int index = 0; index < maxMatchs; index++) {
					SendTo(matchs[index], buffer, writeBuffer.GetActiveBufferSize());
				}

				// 3.5.2. 移除房间
				m_servers[pServer].games.erase(m_servers[pServer].games.begin());
			}
		}
	}
}

//
// 匹配
//
BOOL CPVPGateServer::Match(int evaluation, const PlayerStatus &player, CIOContext *matchs[], int &indexMatch, int maxMatchs)
{
	if (indexMatch < maxMatchs) {
		for (std::map<DWORD, PlayerStatus>::iterator itMatchPlayer = m_evaluations[evaluation].begin(); itMatchPlayer != m_evaluations[evaluation].end(); ++itMatchPlayer) {
			if (player.pContext->guid == itMatchPlayer->second.pContext->guid ||
				player.maxEvaluation < itMatchPlayer->second.minEvaluation ||
				player.minEvaluation > itMatchPlayer->second.maxEvaluation) {
				continue;
			}

			if (matchs) {
				matchs[indexMatch] = itMatchPlayer->second.pContext;
				itMatchPlayer = m_evaluations[evaluation].erase(itMatchPlayer);
			}

			indexMatch++;

			if (indexMatch == maxMatchs) {
				break;
			}
		}
	}

	return indexMatch == maxMatchs ? TRUE : FALSE;
}
