#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "Common.h"
#include "IOCP.h"
#include "Client.pb.h"

void main()
{
	BYTE buffer[1204];
	memset(buffer, 0, sizeof(buffer));
	Client::Login login;
	login.set_guid(123);
	login.set_version(456);
	login.SerializeToArray(buffer, sizeof(buffer));
	int size = login.ByteSize();

	Client::Login aaa;
	aaa.ParseFromArray(buffer, size);
	printf("%d\n", aaa.guid());
	printf("%d\n", aaa.version());

	getch();
}
