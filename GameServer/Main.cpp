#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "IOCP.h"
#include "Client.pb.h"

void main()
{
	int size;
	BYTE data[10];
	BYTE buffer[1024];

	Client::Heart protoHeart;
	Client::Login protoLogin;
	Client::Flags protoFlags;
	Client::CreateGame protoCreateGame;
	Client::DestroyGame protoDestroyGame;
	Client::EnterGame protoEnterGame;
	Client::ExitGame protoExitGame;
	Client::SendToPlayer protoSendToPlayer;
	Client::SendToPlayerAll protoSendToPlayerAll;
	Client::SendToPlayerFilterAll protoSendToPlayerFilterAll;

	protoHeart.set_timestamp(tick());
	protoHeart.SerializeToArray(buffer, sizeof(buffer));
	size = protoHeart.ByteSize();

	protoLogin.set_guid(100);
	protoLogin.set_version(200);
	protoLogin.SerializeToArray(buffer, sizeof(buffer));
	size = protoLogin.ByteSize();

	protoFlags.set_flags(0xffff0000);
	protoFlags.SerializeToArray(buffer, sizeof(buffer));
	size = protoFlags.ByteSize();

	protoCreateGame.set_name("Fuck");
	protoCreateGame.set_password("You");
	protoCreateGame.set_map(100);
	protoCreateGame.set_mode(200);
	protoCreateGame.SerializeToArray(buffer, sizeof(buffer));
	size = protoCreateGame.ByteSize();

	protoEnterGame.set_id(100);
	protoEnterGame.set_password("FuckYou");
	protoEnterGame.SerializeToArray(buffer, sizeof(buffer));
	size = protoEnterGame.ByteSize();

	protoExitGame.SerializeToArray(buffer, sizeof(buffer));
	size = protoExitGame.ByteSize();

	protoSendToPlayer.set_guid(100);
	protoSendToPlayer.set_data("FuckYou!!!");
	protoSendToPlayer.SerializeToArray(buffer, sizeof(buffer));
	size = protoSendToPlayer.ByteSize();

	memset(data, 0, sizeof(data));
	data[0] = 10;
	data[9] = 20;
	protoSendToPlayerAll.set_data((const char *)data, sizeof(data));
	protoSendToPlayerAll.SerializeToArray(buffer, sizeof(buffer));
	size = protoSendToPlayerAll.ByteSize();

	memset(data, 0, sizeof(data));
	Client::SendToPlayerAll protoSendToPlayerAllTest;
	protoSendToPlayerAllTest.ParseFromArray(buffer, size);
	memcpy(data, protoSendToPlayerAllTest.data().c_str(), sizeof(data));

	protoSendToPlayerFilterAll.set_filter(0xffff0000);
	protoSendToPlayerFilterAll.set_data("FuckYou!!!");
	protoSendToPlayerFilterAll.SerializeToArray(buffer, sizeof(buffer));
	size = protoSendToPlayerFilterAll.ByteSize();

	getch();
}
