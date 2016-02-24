#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Common.h"
#include "CacheBuffer.h"


class CSerializer
{
	typedef enum { SERIALIZER_NONE = -1, SERIALIZER_WRITTING, SERIALIZER_READING } STATE;


	// 构造/析构函数
public:
	CSerializer(void);
	virtual ~CSerializer(void);


	// 方法
public:
	void BeginWriting(CCacheBuffer *pBuffer, BOOL bLock = FALSE);                                  // 开始写入
	void EndWriting(BOOL bUnlock = FALSE);                                                         // 结束写入
	void Write(unsigned char *pData, int size);                                                    // 写入

	void BeginReading(CCacheBuffer *pBuffer, BOOL bLock = FALSE);                                  // 开始读取
	void EndReading(BOOL bUnlock = FALSE);                                                         // 结束读取
	void Read(unsigned char *pData, int size);                                                     // 读取

	BOOL IsWritting(void) const;                                                                   // 获得写入状态
	BOOL IsReading(void) const;                                                                    // 获得读取状态

public:
	template <typename T>
	CSerializer& operator << (const T& x)                                                          // 写入
	{
		if (m_pWriteBuffer) {
			m_pWriteBuffer->PushData((unsigned char *)&x, sizeof(x));
		}

		return *this;
	}

	CSerializer& operator << (const char *x)                                                       // 写入字符串
	{
		if (m_pWriteBuffer) {
			int len = (int)strlen(x);

			m_pWriteBuffer->PushData((unsigned char *)&len, sizeof(len));
			m_pWriteBuffer->PushData((unsigned char *)x, sizeof(*x) * len);
		}

		return *this;
	}

public:
	template <typename T>
	CSerializer& operator >> (T& x)                                                                // 读取
	{
		if (m_pReadBuffer) {
			m_pReadBuffer->PopData((unsigned char *)&x, sizeof(x));
		}

		return *this;
	}

	CSerializer& operator >> (char *x)                                                             // 读取字符串
	{
		if (m_pReadBuffer) {
			int len;

			m_pReadBuffer->PopData((unsigned char *)&len, sizeof(len));
			m_pReadBuffer->PopData((unsigned char *)x, sizeof(*x) * len);
		}

		return *this;
	}


	// 属性
protected:
	STATE m_state;                                                                                 // 状态
	CCacheBuffer *m_pReadBuffer;                                                                   // 读缓冲
	CCacheBuffer *m_pWriteBuffer;                                                                  // 写缓冲
};
