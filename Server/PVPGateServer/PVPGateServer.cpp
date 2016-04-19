#include "PVPGateServer.h"


CPVPGateServer::CPVPGateServer(void)
{
	m_maxTimeOut = 100.0f;
	m_maxMatchs = 6;
	m_minEvaluation = 0;
	m_maxEvaluation = 10000;
}

CPVPGateServer::~CPVPGateServer(void)
{

}
