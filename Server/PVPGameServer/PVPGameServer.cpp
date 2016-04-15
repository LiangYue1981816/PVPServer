#include "PVPGameServer.h"


CPVPGameServer::CPVPGameServer(void)
{

}

CPVPGameServer::~CPVPGameServer(void)
{

}

//
// 分配游戏
//
BOOL CPVPGameServer::AllocGames(int maxGames)
{
	//
	// 1. 分配游戏存储
	//
	m_curGames = 0;
	m_maxGames = maxGames;
	m_games = new CGame*[m_maxGames];

	//
	// 2. 建立游戏链表
	//
	for (int indexGame = 0; indexGame < m_maxGames; indexGame++) {
		m_games[indexGame] = new CPVPGame(this);
		m_games[indexGame]->id = indexGame;
	}

	for (int indexGame = 0; indexGame < m_maxGames - 1; indexGame++) {
		m_games[indexGame]->pNext = m_games[indexGame + 1];
		m_games[indexGame + 1]->pNext = NULL;
	}

	m_pFreeGame = m_games[0];
	m_pActiveGame = NULL;

	return TRUE;
}

//
// 分配玩家
//
BOOL CPVPGameServer::AllocPlayers(int maxPlayers)
{
	//
	// 1. 分配上下文存储
	//
	m_curContexts = 0;
	m_maxContexts = maxPlayers;
	m_contexts = new CIOContext*[m_maxContexts];

	//
	// 2. 建立玩家链表
	//
	for (int indexContext = 0; indexContext < m_maxContexts; indexContext++) {
		m_contexts[indexContext] = new CPVPPlayer(this);
		m_contexts[indexContext]->id = indexContext;
	}

	for (int indexContext = 0; indexContext < m_maxContexts - 1; indexContext++) {
		m_contexts[indexContext]->pNext = m_contexts[indexContext + 1];
		m_contexts[indexContext + 1]->pNext = NULL;
	}

	m_pFreeContext = m_contexts[0];
	m_pActiveContext = NULL;

	return TRUE;
}
