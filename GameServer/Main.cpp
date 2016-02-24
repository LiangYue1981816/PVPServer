#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "CacheBuffer.h"

void main()
{
	CCacheBuffer buffer(10);

	char data[1024];
	char szString[] = "Hello";

	for (int index = 0; index < 10; index++) {
		buffer.PushData((unsigned char *)szString, sizeof(szString));
		buffer.PopData((unsigned char *)data, sizeof(szString));
	}

	getch();
}
