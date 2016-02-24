#include "Serializer.h"


CSerializer::CSerializer(void)
	: m_state(SERIALIZER_NONE)
	, m_pReadBuffer(NULL)
	, m_pWriteBuffer(NULL)
{

}

CSerializer::~CSerializer(void)
{

}

//
// 开始写入
//
void CSerializer::BeginWriting(CCacheBuffer *pBuffer, BOOL bLock)
{
	if (pBuffer) {
		m_pWriteBuffer = pBuffer;

		if (bLock) {
			m_pWriteBuffer->Lock();
		}

		m_state = SERIALIZER_WRITTING;
	}
}

//
// 结束写入
//
void CSerializer::EndWriting(BOOL bUnlock)
{
	if (m_pWriteBuffer) {
		if (bUnlock) {
			m_pWriteBuffer->Unlock();
		}

		m_pWriteBuffer = NULL;
		m_state = SERIALIZER_NONE;
	}
}

//
// 写入
//
void CSerializer::Write(unsigned char *pData, int size)
{
	if (m_pWriteBuffer) {
		m_pWriteBuffer->PushData(pData, size);
	}
}

//
// 开始读取
//
void CSerializer::BeginReading(CCacheBuffer *pBuffer, BOOL bLock)
{
	if (pBuffer) {
		m_pReadBuffer = pBuffer;

		if (bLock) {
			m_pReadBuffer->Lock();
		}

		m_state = SERIALIZER_READING;
	}
}

//
// 结束读取
//
void CSerializer::EndReading(BOOL bUnlock)
{
	if (m_pReadBuffer) {
		if (bUnlock) {
			m_pReadBuffer->Unlock();
		}

		m_pReadBuffer = NULL;
		m_state = SERIALIZER_NONE;
	}
}

//
// 读取
//
void CSerializer::Read(unsigned char *pData, int size)
{
	if (m_pReadBuffer) {
		m_pReadBuffer->PopData(pData, size);
	}
}

//
// 获得写入状态
//
BOOL CSerializer::IsWritting(void) const
{
	return m_state == SERIALIZER_WRITTING ? TRUE : FALSE;
}

//
// 获得读取状态
//
BOOL CSerializer::IsReading(void) const
{
	return m_state == SERIALIZER_READING ? TRUE : FALSE;
}
