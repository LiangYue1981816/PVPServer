#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "GateServer.h"

void main()
{
	CGateServer server;
	server.Start("127.0.0.1", 10000, 10000, 10);
	getch();
	server.Stop();
}
