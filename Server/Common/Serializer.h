#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <google/protobuf/stubs/common.h>
#include <google/protobuf/message.h>

#include "Common.h"
#include "CacheBuffer.h"


_ServerExport void Serializer(CCacheBuffer *pBuffer, ::google::protobuf::Message *message, WORD msg);
_ServerExport BOOL Parser(CCacheBuffer *pBuffer, ::google::protobuf::Message *message, WORD size);
