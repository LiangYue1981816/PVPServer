#pragma once


#include <map>
#include <vector>
#include <string>
#include "IOCP.h"
#include "Serializer.h"
#include "ProtoGateClient.pb.h"
#include "ProtoGateServer.pb.h"
#include "ProtoGameServer.pb.h"


//
// 服务器
//
class _ServerExport CGateServer : public CIOCPServer
{
	// 数据结构
public:
	typedef struct {
		CIOContext *pContext;                                                                      // 玩家上下文
		float timeout;                                                                             // 玩家匹配超时
		int minEvaluation;                                                                         // 最小匹配范围
		int maxEvaluation;                                                                         // 最大匹配范围
	} PlayerStatus;

	typedef struct {
		BOOL bEmpty;                                                                               // 空房间
		int id;                                                                                    // 游戏ID
		int mode;                                                                                  // 游戏模式
		int mapid;                                                                                 // 游戏地图
		int evaluation;                                                                            // 游戏评估
	} GameStatus;

	typedef struct {
		char ip[260];                                                                              // 游戏服务器IP
		int port;                                                                                  // 游戏服务器端口
		int curGames;                                                                              // 游戏服务器当前游戏数
		int maxGames;                                                                              // 游戏服务器最大游戏数
		std::vector<GameStatus> games;                                                             // 游戏集合(可加入)
	} GameServerStatus;

	typedef std::map<DWORD, CIOContext*> PlayerMap;                                                // 玩家集合
	typedef std::map<CIOContext*, GameServerStatus> GameServerMap;                                 // 游戏服务器集合
	typedef std::map<int, std::map<DWORD, PlayerStatus>> PlayerEvaluationMap;                      // 待匹配玩家集合


	// 构造/析构函数
public:
	CGateServer(void);
	virtual ~CGateServer(void);


	// 方法
public:
	virtual BOOL Start(const char *ip, int port, int maxContexts, int timeOut);                    // 启动服务器
	virtual void Stop(void);                                                                       // 停止服务器

protected:
	virtual BOOL CreateUpdateThread(void);                                                         // 创建更新线程
	virtual void DestroyUpdateThread(void);                                                        // 销毁更新线程

protected:
	virtual BOOL Login(CIOContext *pContext, DWORD guid);                                          // 登陆
	virtual BOOL Logout(CIOContext *pContext);                                                     // 注销
	virtual CIOContext* QueryContext(DWORD guid);                                                  // 查询

	virtual void ClearGameServer(CIOContext *pContext);                                            // 清理游戏服务器

protected:
	virtual void SendTo(CIOContext *pContext, BYTE *pBuffer, size_t size);                         // 发送指定客户端

protected:
	virtual void OnConnect(CIOContext *pContext, SOCKET acceptSocket);                             // 客户端链接回调
	virtual void OnDisconnect(CIOContext *pContext);                                               // 客户端断链回调

	virtual void OnUpdateRecv(DWORD dwDeltaTime);                                                  // 更新接收消息
	virtual void OnUpdateMatch(DWORD dwDeltaTime);                                                 // 更新匹配

	virtual void OnHeartReset(CIOContext *pContext);                                               // 重置心跳
	virtual void OnHeart(CIOContext *pContext, WORD size);                                         // 心跳
	virtual void OnLogin(CIOContext *pContext, WORD size);                                         // 登陆
	virtual void OnMatch(CIOContext *pContext, WORD size);                                         // 匹配
	virtual void OnCancelMatch(CIOContext *pContext, WORD size);                                   // 取消匹配
	virtual void OnListGameServer(CIOContext *pContext, WORD size);                                // 游戏服务器列表
	virtual void OnSendToPlayer(CIOContext *pContext, WORD size);                                  // 发送指定玩家
	virtual void OnGameServerStatus(CIOContext *pContext, WORD size);                              // 游戏服务器状态

protected:
	virtual void Monitor(void);                                                                    // 监控

protected:
	static DWORD WINAPI UpdateThread(LPVOID lpParam);                                              // 更新线程


	// 属性
protected:
	HANDLE m_hUpdateThread;                                                                        // 更新线程句柄

	PlayerMap m_players;                                                                           // 玩家集合
	GameServerMap m_servers;                                                                       // 游戏服务器集合
	PlayerEvaluationMap m_evaluations;                                                             // 待匹配玩家集合

protected:
	DWORD m_dwUpdateCount;                                                                         // 更新次数
	DWORD m_dwUpdateTime;                                                                          // 平均更新时间
	DWORD m_dwUpdateTimeTotal;                                                                     // 更新总时间
	DWORD m_dwRuntimeTotal;                                                                        // 总运行时间

	DWORD m_dwRecvDataSize;                                                                        // 接收数据量
	DWORD m_dwSendDataSize;                                                                        // 发送数据量
};
