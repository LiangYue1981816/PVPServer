#pragma once


enum {
	ERR_NONE = 0,                                                                                  // 无错误

	ERR_VERSION_INVALID,                                                                           // 无效版本

	ERR_PLAYER_BASE = 1000,
	ERR_PLAYER_INVALID,                                                                            // 玩家无效
	ERR_PLAYER_INVALID_ID,                                                                         // 玩家无效ID
	ERR_PLAYER_INVALID_GUID,                                                                       // 玩家无效GUID
	ERR_PLAYER_STATE_LOGIN,                                                                        // 玩家已经登陆
	ERR_PLAYER_IN_GAME,                                                                            // 玩家已经在会话中
	ERR_PLAYER_OUT_GAME,                                                                           // 玩家没有在会话中

	ERR_GAME_BASE = 2000,
	ERR_GAME_INVALID,                                                                              // 游戏无效
	ERR_GAME_INVALID_ID,                                                                           // 游戏无效ID
	ERR_GAME_USING,                                                                                // 游戏中
	ERR_GAME_EMPTY,                                                                                // 游戏空
	ERR_GAME_FULL,                                                                                 // 游戏满
	ERR_GAME_PASSWORD,                                                                             // 会话密码错误

	ERR_SERVER_BASE = 3000,
	ERR_SERVER_FULL,                                                                               // 服务器满

	ERR_GAMEPLAY_BASE = 4000,
	ERR_GAMEPLAY_INVALID_MODE,                                                                     // 无效游戏模式
};
