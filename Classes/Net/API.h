#ifndef _API_H_
#define _API_H_

#include "Server.h"
#include "Client.h"
#include <map>
#include <thread>

bool RoomHolderClient(Client &_client, unsigned short _port)
{
	_client.Create();
	_client.Connect(_port);
	return true;
}

bool OpenTheRoom(Server &_room, Client &_client, unsigned short _port)
{
	_room.Create();
	_room.Bind(_port);
	_room.Listen(2);
	_room.AllAccept();
	RoomHolderClient(_client, _port);
	return true;
}

bool RoomJoinerClient(Client &_client, unsigned short _port)
{
	_client.Create();
	_client.Connect(_port);
	return true;
}

bool RecvAndSend(Server &_server)
{
	std::thread _task1(&Server::RecvAndSend1, _server);
	std::thread _task2(&Server::RecvAndSend2, _server);
	_task1.detach();
	_task2.detach();
}

bool SendMsgMod(Client &_client)
{
	std::thread _task(&Client::SendMsg, _client);
	_task.detach();
}

bool RecvMod(Client &_client)
{
	std::thread _task(&Client::RecvToMap, _client);
	_task.detach();
}



#endif 