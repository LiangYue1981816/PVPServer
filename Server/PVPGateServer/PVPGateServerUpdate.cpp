#include "PVPGateServer.h"


//
// 更新匹配
//
void CPVPGateServer::OnUpdateMatch(DWORD dwDeltaTime)
{
	static DWORD dwTime = 0;
	static const float maxTimeOut = 10;// 100.0f;
	static const int maxMatchs = 2;
	static const int minEvaluation = 0;
	static const int maxEvaluation = 10000;

	ProtoGateServer::Match responseMatch;

	BYTE buffer[PACK_BUFFER_SIZE];
	CCacheBuffer writeBuffer(sizeof(buffer), buffer);

	//
	// 1. 更新频率检查
	//
	dwTime += dwDeltaTime;
	{
		if (dwTime < 1000) {
			return;
		}
	}
	dwTime = 0;

	//
	// 2. 计算当前玩家匹配范围
	//
	for (PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.begin(); itPlayerMap != m_evaluations.end(); ++itPlayerMap) {
		for (std::map<DWORD, PlayerStatus>::iterator itPlayer = itPlayerMap->second.begin(); itPlayer != itPlayerMap->second.end(); ++itPlayer) {
			itPlayer->second.timeout += 1.0f;

			// 2.1. 计算匹配范围
			//      算法: 随着时间增加线性扩大玩家可匹配范围
			if (itPlayer->second.timeout < maxTimeOut) {
				itPlayer->second.minEvaluation = (int)(itPlayerMap->first - maxEvaluation * itPlayer->second.timeout / maxTimeOut + 0.5f);
				itPlayer->second.maxEvaluation = (int)(itPlayerMap->first + maxEvaluation * itPlayer->second.timeout / maxTimeOut + 0.5f);

				if (itPlayer->second.minEvaluation < minEvaluation) itPlayer->second.minEvaluation = minEvaluation;
				if (itPlayer->second.maxEvaluation > maxEvaluation) itPlayer->second.maxEvaluation = maxEvaluation;
			}
			// 2.2. 匹配超时
			else {
				responseMatch.set_err(ProtoGateServer::ERROR_CODE::ERR_MATCH_TIMEOUT);

				Serializer(&writeBuffer, &responseMatch, ProtoGateServer::RESPONSE_MSG::MATCH);
				SendTo(itPlayer->second.pContext, buffer, writeBuffer.GetActiveBufferSize());

				itPlayer->second.pContext->dwUserData = 0xffffffff;
			}
		}
	}

	//
	// 3. 匹配计算
	//
	for (PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.begin(); itPlayerMap != m_evaluations.end(); ++itPlayerMap) {
		for (std::map<DWORD, PlayerStatus>::iterator itPlayer = itPlayerMap->second.begin(); itPlayer != itPlayerMap->second.end(); ++itPlayer) {
			GameServerMap::iterator itMatchGameServer;
			float minLoadFactor = FLT_MAX;

			CIOContext *matchs[maxMatchs] = { itPlayer->second.pContext };
			BOOL bMatch = FALSE;
			int numMatchs = 1;

			int evaluation = itPlayerMap->first;
			int evaluationOffset = (itPlayer->second.maxEvaluation - itPlayer->second.minEvaluation) / 2;

			// 3.1. 检查失效玩家
			if (itPlayer->second.pContext->dwUserData == 0xffffffff) {
				continue;
			}

			// 3.2. 尝试匹配
			bMatch = FALSE;
			numMatchs = 1;

			for (int offset = 0; offset <= evaluationOffset; offset++) {
				if (offset == 0) {
					bMatch |= Match(evaluation, itPlayer->second, NULL, numMatchs, maxMatchs);
				}
				else {
					if (evaluation - offset >= minEvaluation) bMatch |= Match(evaluation - offset, itPlayer->second, NULL, numMatchs, maxMatchs);
					if (evaluation + offset <= maxEvaluation) bMatch |= Match(evaluation + offset, itPlayer->second, NULL, numMatchs, maxMatchs);
				}
			}

			if (bMatch == FALSE) {
				continue;
			}

			// 3.3. 选择服务器
			minLoadFactor = FLT_MAX;
			itMatchGameServer = m_servers.end();

			for (GameServerMap::iterator itGameServer = m_servers.begin(); itGameServer != m_servers.end(); ++itGameServer) {
				if (itGameServer->second.games.empty() == false) {
					float factor = 1.0f * itGameServer->second.curGames / itGameServer->second.maxGames;

					if (minLoadFactor > factor) {
						minLoadFactor = factor;
						itMatchGameServer = itGameServer;
					}
				}
			}

			if (itMatchGameServer == m_servers.end()) {
				continue;
			}

			// 3.4. 正式匹配
			bMatch = FALSE;
			numMatchs = 1;

			for (int offset = 0; offset <= evaluationOffset; offset++) {
				if (offset == 0) {
					bMatch |= Match(evaluation, itPlayer->second, matchs, numMatchs, maxMatchs);
				}
				else {
					if (evaluation - offset >= minEvaluation) bMatch |= Match(evaluation - offset, itPlayer->second, matchs, numMatchs, maxMatchs);
					if (evaluation + offset <= maxEvaluation) bMatch |= Match(evaluation + offset, itPlayer->second, matchs, numMatchs, maxMatchs);
				}
			}

			// 3.5. 发送匹配消息
			responseMatch.set_err(ProtoGateServer::ERROR_CODE::ERR_NONE);
			responseMatch.set_ip(itMatchGameServer->second.ip);
			responseMatch.set_port(itMatchGameServer->second.port);
			responseMatch.set_gameid(itMatchGameServer->second.games.begin()->id);

			Serializer(&writeBuffer, &responseMatch, ProtoGateServer::RESPONSE_MSG::MATCH);

			for (int index = 0; index < maxMatchs; index++) {
				matchs[index]->dwUserData = 0xffffffff;
				SendTo(matchs[index], buffer, writeBuffer.GetActiveBufferSize());
			}

			// 3.6. 移除房间
			itMatchGameServer->second.games.erase(itMatchGameServer->second.games.begin());
		}
	}

	//
	// 4. 清理
	//
	for (PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.begin(); itPlayerMap != m_evaluations.end();) {
		for (std::map<DWORD, PlayerStatus>::iterator itPlayer = itPlayerMap->second.begin(); itPlayer != itPlayerMap->second.end();) {
			if (itPlayer->second.pContext->dwUserData == 0xffffffff) {
				itPlayerMap->second.erase(itPlayer++);
				continue;
			}

			++itPlayer;
		}

		if (itPlayerMap->second.empty()) {
			m_evaluations.erase(itPlayerMap++);
			continue;
		}

		++itPlayerMap;
	}

	for (GameServerMap::iterator itGameServer = m_servers.begin(); itGameServer != m_servers.end();) {
		if (itGameServer->second.games.empty()) {
			m_servers.erase(itGameServer++);
			continue;
		}

		++itGameServer;
	}
}

//
// 匹配
//
BOOL CPVPGateServer::Match(int evaluation, const PlayerStatus &player, CIOContext *matchs[], int &indexMatch, int maxMatchs)
{
	if (indexMatch < maxMatchs) {
		PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.find(evaluation);

		if (itPlayerMap != m_evaluations.end()) {
			for (std::map<DWORD, PlayerStatus>::iterator itMatchPlayer = itPlayerMap->second.begin(); itMatchPlayer != itPlayerMap->second.end(); ++itMatchPlayer) {
				if (itMatchPlayer->second.pContext->dwUserData == 0xffffffff) {
					continue;
				}
				if (player.pContext->guid == itMatchPlayer->second.pContext->guid) {
					continue;
				}
				if (player.maxEvaluation < itMatchPlayer->second.minEvaluation ||
					player.minEvaluation > itMatchPlayer->second.maxEvaluation) {
					continue;
				}

				if (matchs) {
					matchs[indexMatch] = itMatchPlayer->second.pContext;
				}

				indexMatch++;

				if (indexMatch == maxMatchs) {
					break;
				}
			}
		}
	}

	return indexMatch == maxMatchs ? TRUE : FALSE;
}
