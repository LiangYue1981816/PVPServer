#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "PVPGateServer.h"

void main(int argc, char* argv[])
{
	const char *ip = argv[1];
	int port = atoi(argv[2]);

	CPVPGateServer server;
	server.Start(ip, port, 20000, 10);
	getch();
	server.Stop();
}
