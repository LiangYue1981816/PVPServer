#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "PVPGameServer.h"

#define MAX_GAMES                      50
#define MAX_GAME_PLAYERS               10

void main(int argc, char* argv[])
{
	const char *ip = argv[1];
	int port = atoi(argv[2]);

	const char* gateip = argv[3];
	int gateport = atoi(argv[4]);

	CPVPGameServer server;
	server.Start(ip, port, MAX_GAMES, MAX_GAME_PLAYERS, 10, gateip, gateport);
	getch();
	server.Stop();
}
