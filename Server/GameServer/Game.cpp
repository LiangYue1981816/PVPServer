#include "GameServer.h"


CGame::CGame(CGameServer *s)
	: id(0xffffffff)

	, pServer(s)
	, pActivePlayer(NULL)

	, m_mode(-1)
	, m_mapid(-1)
	, m_maxPlayers(0)
	, m_numPlayers(0)

	, pNext(NULL)
	, pNextActive(NULL)
	, pPrevActive(NULL)
{
	memset(m_szPassword, 0, sizeof(m_szPassword));
}

CGame::~CGame(void)
{

}

//
// 设置游戏
//
void CGame::SetGame(const char *password, int mode, int mapid, int maxPlayers)
{
	m_mode = mode;
	m_mapid = mapid;
	m_maxPlayers = maxPlayers;
	strcpy(m_szPassword, password);
}

//
// 获得游戏模式
//
int CGame::GetMode(void) const
{
	return m_mode;
}

//
// 获得游戏地图
//
int CGame::GetMapID(void) const
{
	return m_mapid;
}

//
// 获得当前玩家数
//
int CGame::GetPlayers(void) const
{
	return m_numPlayers;
}

//
// 获得最大玩家数
//
int CGame::GetMaxPlayers(void) const
{
	return m_maxPlayers;
}

//
// 添加玩家
//
int CGame::AddPlayer(CPlayer *pPlayer, const char *password, BOOL bCreater)
{
	//
	// 1. 参数安全检查
	//
	if (pPlayer == NULL) {
		return ErrorCode::Code::ERR_PLAYER_INVALID;
	}

	if (pPlayer->pGame != NULL) {
		return ErrorCode::Code::ERR_PLAYER_FLAGS_INGAME;
	}

	if (IsFull() == TRUE) {
		return ErrorCode::Code::ERR_GAME_FULL;
	}

	if (IsEmpty() == FALSE && bCreater == TRUE) {
		return ErrorCode::Code::ERR_GAME_USING;
	}

	if (IsEmpty() == TRUE && bCreater == FALSE) {
		return ErrorCode::Code::ERR_GAME_EMPTY;
	}

	if (password == NULL ||
		strncmp(password, m_szPassword, sizeof(m_szPassword))) {
		return ErrorCode::Code::ERR_GAME_PASSWORD;
	}

	//
	// 2. 添加玩家
	//
	pPlayer->pGame = this;

	pPlayer->pPrevPlayer = NULL;
	pPlayer->pNextPlayer = pActivePlayer;

	if (pActivePlayer) {
		pActivePlayer->pPrevActive = pPlayer;
	}

	pActivePlayer = pPlayer;

	//
	// 3. 设置玩家状态
	//
	pPlayer->EnableFlag(FlagsCode::Code::PLAYER_FLAGS_WAITING);

	//
	// 4. 记录玩家
	//
	m_numPlayers++;

	return ErrorCode::Code::ERR_NONE;
}

//
// 删除玩家
//
int CGame::DelPlayer(CPlayer *pPlayer)
{
	//
	// 1. 参数安全检查
	//
	if (pPlayer == NULL) {
		return ErrorCode::Code::ERR_PLAYER_INVALID;
	}

	if (pPlayer->pGame != this) {
		return ErrorCode::Code::ERR_PLAYER_FLAGS_NOT_INGAME;
	}

	//
	// 2. 删除玩家
	//
	pPlayer->pGame = NULL;

	if (pPlayer->pPrevPlayer) {
		pPlayer->pPrevPlayer->pNextPlayer = pPlayer->pNextPlayer;
	}

	if (pPlayer->pNextPlayer) {
		pPlayer->pNextPlayer->pPrevPlayer = pPlayer->pPrevPlayer;
	}

	if (pActivePlayer == pPlayer) {
		pActivePlayer = pPlayer->pNextPlayer;
	}

	pPlayer->pPrevPlayer = NULL;
	pPlayer->pNextPlayer = NULL;

	//
	// 3. 设置玩家状态
	//
	pPlayer->SetFlags(FlagsCode::Code::PLAYER_FLAGS_LOGIN);

	//
	// 4. 记录玩家
	//
	m_numPlayers--;

	return ErrorCode::Code::ERR_NONE;
}

//
// 清空玩家
//
void CGame::Clear(void)
{
	while (pActivePlayer) {
		DelPlayer(pActivePlayer);
	}
}

//
// 房间满判断
//
BOOL CGame::IsFull(void)
{
	return m_numPlayers == m_maxPlayers ? TRUE : FALSE;
}

//
// 房间空判断
//
BOOL CGame::IsEmpty(void)
{
	return m_numPlayers == 0 ? TRUE : FALSE;
}

//
// 更新
//
void CGame::Update(float deltaTime)
{

}
