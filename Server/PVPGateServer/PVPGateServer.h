#pragma once


#include "GateServer.h"


class _ServerExport CPVPGateServer : public CGateServer
{
	// 构造/析构函数
public:
	CPVPGateServer(void);
	virtual ~CPVPGateServer(void);


	// 方法
protected:
	virtual void OnUpdateMatch(DWORD dwDeltaTime);                                                 // 更新匹配


	// 属性
protected:
};
