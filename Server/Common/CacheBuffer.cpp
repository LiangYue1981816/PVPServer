#include "CacheBuffer.h"


CCacheBuffer::CCacheBuffer(size_t size)
	: m_totalBufferSize(size)
	, m_activeBufferSize(0)

	, m_bAllocBuffer(TRUE)
	, m_pBuffer(NULL)
	, m_pPushPointer(NULL)
	, m_pPopPointer(NULL)
{
	//
	// 1. 初始化互斥量
	//
	pthread_mutex_init(&m_mutex, NULL);

	//
	// 2. 分配数据缓冲并初始化
	//
	m_pBuffer = (unsigned char *)malloc(size);
	m_pPopPointer = m_pBuffer;
	m_pPushPointer = m_pBuffer;

	memset(m_pBuffer, 0xc, m_totalBufferSize);
}

CCacheBuffer::CCacheBuffer(size_t size, unsigned char *pBuffer)
	: m_totalBufferSize(size)
	, m_activeBufferSize(0)

	, m_bAllocBuffer(FALSE)
	, m_pBuffer(NULL)
	, m_pPushPointer(NULL)
	, m_pPopPointer(NULL)
{
	//
	// 1. 初始化互斥量
	//
	pthread_mutex_init(&m_mutex, NULL);

	//
	// 2. 初始化数据缓冲
	//
	m_pBuffer = pBuffer;
	m_pPopPointer = m_pBuffer;
	m_pPushPointer = m_pBuffer;

	memset(m_pBuffer, 0xc, m_totalBufferSize);
}

CCacheBuffer::~CCacheBuffer(void)
{
	//
	// 1. 释放缓冲
	//
	if (m_bAllocBuffer && m_pBuffer) {
		free(m_pBuffer);
	}

	//
	// 2. 销毁互斥量
	//
	pthread_mutex_destroy(&m_mutex);
}

//
// 锁定
//
void CCacheBuffer::Lock(void)
{
	pthread_mutex_lock(&m_mutex);
}

//
// 解锁
//
void CCacheBuffer::Unlock(void)
{
	pthread_mutex_unlock(&m_mutex);
}

//
// 获得缓冲总尺寸
//
size_t CCacheBuffer::GetTotalBufferSize(void)
{
	return m_totalBufferSize;
}

//
// 获得活动缓冲尺寸
//
size_t CCacheBuffer::GetActiveBufferSize(void)
{
	return m_activeBufferSize;
}

//
// 获得可用缓冲尺寸
//
size_t CCacheBuffer::GetFreeBufferSize(void)
{
	return m_totalBufferSize - m_activeBufferSize;
}

//
// 清空缓冲
//
void CCacheBuffer::ClearBuffer(void)
{
	if (m_pBuffer) {
		m_activeBufferSize = 0;

		m_pPopPointer = m_pBuffer;
		m_pPushPointer = m_pBuffer;

		memset(m_pBuffer, 0xc, m_totalBufferSize);
	}
}

//
// 压入数据
//
int CCacheBuffer::PushData(unsigned char *pData, size_t size)
{
	//
	// 1. 缓冲检查
	//
	if (pData == NULL || m_pBuffer == NULL) {
		return -1;
	}

	if (size == 0 || size > GetFreeBufferSize()) {
		return 0;
	}

	//
	// 2. 压入数据
	//
	size_t sizeParts[2];

	sizeParts[0] = min(m_totalBufferSize + (size_t)(m_pBuffer - m_pPushPointer), size);
	sizeParts[1] = size - sizeParts[0];

	_PushData(pData, sizeParts[0]);
	_PushData(pData + sizeParts[0], sizeParts[1]);

	return (int)size;
}

void CCacheBuffer::_PushData(unsigned char *pData, size_t size)
{
	memcpy(m_pPushPointer, pData, size);

	if (m_pPushPointer + size < m_pBuffer + m_totalBufferSize) {
		m_pPushPointer += size;
	}
	else {
		m_pPushPointer = m_pBuffer;
	}

	m_activeBufferSize += size;
}

//
// 弹出数据
//
int CCacheBuffer::PopData(unsigned char *pData, size_t size)
{
	//
	// 1. 缓冲检查
	//
	if (pData == NULL || m_pBuffer == NULL) {
		return -1;
	}

	if (size == 0 || size > GetActiveBufferSize()) {
		return 0;
	}

	//
	// 2. 弹出数据
	//
	size_t sizeParts[2];

	sizeParts[0] = min(m_totalBufferSize + (size_t)(m_pBuffer - m_pPopPointer), size);
	sizeParts[1] = size - sizeParts[0];

	_PopData(pData, sizeParts[0]);
	_PopData(pData + sizeParts[0], sizeParts[1]);

	return (int)size;
}

//
// 获得数据
//
int CCacheBuffer::GetData(unsigned char *pData, size_t size)
{
	//
	// 1. 缓冲检查
	//
	if (pData == NULL || m_pBuffer == NULL) {
		return -1;
	}

	if (size == 0 || size > GetActiveBufferSize()) {
		return 0;
	}

	//
	// 2. 获得数据
	//
	size_t sizeParts[2];

	sizeParts[0] = min(m_totalBufferSize + (size_t)(m_pBuffer - m_pPopPointer), size);
	sizeParts[1] = size - sizeParts[0];

	size_t activeBufferSize = m_activeBufferSize;
	unsigned char *pPopPointer = m_pPopPointer;
	{
		_PopData(pData, sizeParts[0]);
		_PopData(pData + sizeParts[0], sizeParts[1]);
	}
	m_activeBufferSize = activeBufferSize;
	m_pPopPointer = pPopPointer;

	return (int)size;
}

void CCacheBuffer::_PopData(unsigned char *pData, size_t size)
{
	memcpy(pData, m_pPopPointer, size);

	if (m_pPopPointer + size < m_pBuffer + m_totalBufferSize) {
		m_pPopPointer += size;
	}
	else {
		m_pPopPointer = m_pBuffer;
	}

	m_activeBufferSize -= size;
}
