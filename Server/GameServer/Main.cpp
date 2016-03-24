#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "GameServer.h"

#define MAX_GAMES                      50
#define MAX_GAME_PLAYERS               10

void main()
{
	CGameServer server;
	server.Start("127.0.0.1", 20000, MAX_GAMES, MAX_GAME_PLAYERS, 120, "127.0.0.1", 10000);
	getch();
	server.Stop();
}
