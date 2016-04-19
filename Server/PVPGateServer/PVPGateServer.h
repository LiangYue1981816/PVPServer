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
	virtual BOOL Match(int evaluation, const PlayerStatus &player, CIOContext *matchs[], int &indexMatch, int maxMatchs); // 匹配


	// 属性
protected:
	int m_maxMatchs;                                                                               // 最大匹配数
	float m_maxTimeOut;                                                                            // 匹配超时
	CIOContext **m_matchs;                                                                         // 匹配集合
};
