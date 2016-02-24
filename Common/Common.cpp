#include "Common.h"


DWORD HashValue(const char *szString)
{
	if (!szString) {
		return 0xffffffff;
	}

	DWORD dwHashValue = 0;
	const char *c = szString;

	while (*c) {
		dwHashValue = (dwHashValue << 5) - dwHashValue + (*c == '/' ? '\\' : *c);
		c++;
	}

	return dwHashValue;
}
