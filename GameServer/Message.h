#pragma once


enum {
	GAMESERVER_MSG_BASE = 3000,
	GAMESERVER_MSG_C2S_BASE = GAMESERVER_MSG_BASE + 100,
	GAMESERVER_MSG_S2C_BASE = GAMESERVER_MSG_BASE + 200,

	GAMESERVER_MSG_C2S_HEART = GAMESERVER_MSG_C2S_BASE + 0,                                        // 心跳
	GAMESERVER_MSG_C2S_LOGIN = GAMESERVER_MSG_C2S_BASE + 1,                                        // 登录
	GAMESERVER_MSG_C2S_FLAGS = GAMESERVER_MSG_C2S_BASE + 2,                                        // 设置标识
	GAMESERVER_MSG_C2S_CREATE_GAME = GAMESERVER_MSG_C2S_BASE + 3,                                  // 创建游戏
	GAMESERVER_MSG_C2S_DESTROY_GAME = GAMESERVER_MSG_C2S_BASE + 4,                                 // 销毁游戏
	GAMESERVER_MSG_C2S_ENTER_GAME = GAMESERVER_MSG_C2S_BASE + 5,                                   // 进入游戏
	GAMESERVER_MSG_C2S_EXIT_GAME = GAMESERVER_MSG_C2S_BASE + 6,                                    // 退出游戏
	GAMESERVER_MSG_C2S_MODIFY_GAME_PASSWORD = GAMESERVER_MSG_C2S_BASE + 7,                         // 修改游戏密码
	GAMESERVER_MSG_C2S_SENDTO_PLAYER = GAMESERVER_MSG_C2S_BASE + 8,                                // 发送指定玩家
	GAMESERVER_MSG_C2S_SENDTO_PLAYER_ALL = GAMESERVER_MSG_C2S_BASE + 9,                            // 发送所有玩家
	GAMESERVER_MSG_C2S_COUNT,

	GAMESERVER_MSG_S2C_HEART = GAMESERVER_MSG_S2C_BASE + 1,                                        // 心跳
	GAMESERVER_MSG_S2C_LOGIN = GAMESERVER_MSG_S2C_BASE + 2,                                        // 登入
	GAMESERVER_MSG_S2C_FLAGS = GAMESERVER_MSG_S2C_BASE + 3,                                        // 设置标识
	GAMESERVER_MSG_S2C_CREATE_GAME = GAMESERVER_MSG_S2C_BASE + 4,                                  // 创建游戏
	GAMESERVER_MSG_S2C_DESTROY_GAME = GAMESERVER_MSG_S2C_BASE + 5,                                 // 销毁游戏
	GAMESERVER_MSG_S2C_ENTER_GAME = GAMESERVER_MSG_S2C_BASE + 6,                                   // 进入游戏
	GAMESERVER_MSG_S2C_EXIT_GAME = GAMESERVER_MSG_S2C_BASE + 7,                                    // 退出游戏
	GAMESERVER_MSG_S2C_MODIFY_GAME_PASSWORD = GAMESERVER_MSG_S2C_BASE + 8,                         // 修改游戏密码
	GAMESERVER_MSG_S2C_SENDTO_PLAYER = GAMESERVER_MSG_S2C_BASE + 9,                                // 转发
	GAMESERVER_MSG_S2C_COUNT,
};
