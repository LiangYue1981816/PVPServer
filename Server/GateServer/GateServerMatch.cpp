#include "GateServer.h"


//
// 更新匹配
//
void CGateServer::OnUpdateMatch(DWORD dwDeltaTime)
{
	//
	// 1. 更新即时检查
	//
	static DWORD dwTime = 0;

	dwTime += dwDeltaTime;

	if (dwTime < 1000) {
		return;
	}

	dwTime = 0;

	//
	// 2. 匹配计算
	//
}
