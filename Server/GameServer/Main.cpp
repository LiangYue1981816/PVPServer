#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "GameServer.h"

void main()
{
	CGameServer server;
	server.Start("10.230.72.33", 10000, MAX_GAMES, MAX_GAME_PLAYERS, 120, "", 100000);
	getch();
	server.Stop();
}
