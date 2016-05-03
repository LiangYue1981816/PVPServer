#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pthread.h"
#include "semaphore.h"
#include "Common.h"


class _ServerExport CCacheBuffer
{
	// 构造/析构函数
public:
	CCacheBuffer(void);
	CCacheBuffer(size_t size);
	CCacheBuffer(size_t size, unsigned char *pBuffer);
	virtual ~CCacheBuffer(void);


	// 方法
public:
	void AllocBuffer(size_t size, unsigned char *pBuffer);                                         // 分配缓冲

public:
	size_t GetTotalBufferSize(void);                                                               // 获得缓冲总尺寸
	size_t GetActiveBufferSize(void);                                                              // 获得活动缓冲尺寸
	size_t GetFreeBufferSize(void);                                                                // 获得可用缓冲尺寸

public:
	void ClearBuffer(void);                                                                        // 清空缓冲

	void Lock(void);                                                                               // 锁定
	void Unlock(void);                                                                             // 解锁

	int PushData(unsigned char *pData, size_t size);                                               // 压入数据
	int PopData(unsigned char *pData, size_t size);                                                // 弹出数据
	int GetData(unsigned char *pData, size_t size);                                                // 获得数据

protected:
	void _PushData(unsigned char *pData, size_t size);                                             // 压入数据
	void _PopData(unsigned char *pData, size_t size);                                              // 弹出数据


	// 属性
protected:
	size_t m_totalBufferSize;                                                                      // 缓冲总尺寸
	size_t m_activeBufferSize;                                                                     // 活动缓冲尺寸

	int m_bAllocBuffer;                                                                            // 分配缓冲
	unsigned char *m_pBuffer;                                                                      // 缓冲指针
	unsigned char *m_pPushPointer;                                                                 // 压入指针
	unsigned char *m_pPopPointer;                                                                  // 弹出指针

protected:
	pthread_mutex_t m_mutex;                                                                       // 互斥量
};
