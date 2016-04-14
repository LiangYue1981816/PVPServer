#include "PVPGateServer.h"


//
// 更新匹配
//
void CPVPGateServer::OnUpdateMatch(DWORD dwDeltaTime)
{
	static DWORD dwTime = 0;
	static const float timeOut = 100.0f;
	static const int maxGamePlayers = 6;
	static const DWORD dwMinEvaluation = 0;
	static const DWORD dwMaxEvaluation = 10000;

	//
	// 1. 更新即时检查
	//
	dwTime += dwDeltaTime;

	if (dwTime < 1000) {
		return;
	}

	dwTime = 0;

	//
	// 2. 匹配计算
	//
	for (PlayerEvaluationMap::iterator itPlayerMap = m_evaluations.begin(); itPlayerMap != m_evaluations.end(); ++itPlayerMap) {
		for (std::map<DWORD, PlayerStatus>::iterator itPlayer = itPlayerMap->second.begin(); itPlayer != itPlayerMap->second.end(); ++itPlayer) {
			itPlayer->second.timeout += 1.0f;
		}
	}
}
