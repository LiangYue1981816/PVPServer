#include "PVPGateServer.h"


//
// 更新匹配
//
void CPVPGateServer::OnUpdateMatch(DWORD dwDeltaTime)
{
	static DWORD dwTime = 0;
	static const float maxTimeOut = 100.0f;
	static const int maxGamePlayers = 6;
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
			int numMatchs = 0;

			for (int evaluation = itPlayer->second.minEvaluation; evaluation < itPlayer->second.maxEvaluation; evaluation++) {
				for (std::map<DWORD, PlayerStatus>::iterator itMatchPlayer = m_evaluations[evaluation].begin(); itMatchPlayer != m_evaluations[evaluation].end(); ++itMatchPlayer) {
					if (itPlayer->second.maxEvaluation < itMatchPlayer->second.minEvaluation ||
						itPlayer->second.minEvaluation > itMatchPlayer->second.maxEvaluation) {
						continue;
					}

					numMatchs++;
				}
			}
		}
	}
}
