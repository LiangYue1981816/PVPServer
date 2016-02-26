#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "IOCP.h"

void main()
{
	CIOCPServer server;
	server.Start("127.0.0.1", 10000, 5000);
	server.Stop();
}
