#include "Serializer.h"


void Serializer(CCacheBuffer *pBuffer, ::google::protobuf::Message *message, WORD msg)
{
	WORD fullSize, bodySize;
	BYTE body[PACK_BUFFER_SIZE];

	message->SerializeToArray(body, sizeof(body));
	bodySize = message->ByteSize();
	fullSize = sizeof(msg) + bodySize;

	pBuffer->PushData((unsigned char *)&fullSize, sizeof(fullSize));
	pBuffer->PushData((unsigned char *)&msg, sizeof(msg));
	pBuffer->PushData(body, bodySize);
}

void Parser(CCacheBuffer *pBuffer, ::google::protobuf::Message *message, WORD size)
{
	BYTE body[PACK_BUFFER_SIZE];

	pBuffer->PopData(body, size);
	message->ParseFromArray(body, size);
}
