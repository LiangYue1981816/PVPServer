#pragma once


#include <map>
#include <vector>
#include <string>
#include "IOCP.h"
#include "Serializer.h"


//
// 服务器
//
class CGateServer : public CIOCPServer
{
	// 数据结构
public:


	// 构造/析构函数
public:
	CGateServer(void);
	virtual ~CGateServer(void);


	// 方法
public:


	// 属性
protected:
};

extern void WriteLog(const char *szFmt, ...);                                                      // 输出日志
