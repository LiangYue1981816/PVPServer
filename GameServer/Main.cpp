#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "GameServer.h"

void main()
{
	CGameServer server;
	server.Start("127.0.0.1", 10000, MAX_GAMES, MAX_GAME_PLAYERS, 1000, "", 100000);
	getch();
	server.Stop();
}
