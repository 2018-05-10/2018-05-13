#ifndef _API_H_
#define _API_H_

#include "Server.h"
#include "Client.h"
#include <thread>
static bool RoomHolderClient(Client* _client, unsigned short _port)//不用关心
{
	_client->Create();
	_client->ConnectForHolder(_port);
	return true;
}

static bool OpenTheRoom(Server* _room, Client* _client, unsigned short _port)//创房间者调用，_port取10000~60000(勿用11114)
{
	_room->Create();
	_room->Bind(_port);
	_room->Listen(2);
	std::thread _task(&Server::Broadcast, _room);//时间到了线程会自动退出
	_task.detach();
	RoomHolderClient(_client, _port);
	std::thread _taskOfAccept(&Server::AllAccept, _room);//建立两个连接后线程退出
	_taskOfAccept.detach();
	//_room->AllAccept();
	return true;
}

static bool RoomJoinerClient(Client* _client, unsigned short _port)//加入者调用，_port取相同数字
{
	_client->Create();
	_client->ConnectForJoiner(_port);
	return true;
}

static bool ServerRecvAndSend(Server* _server)
{
	for (int i = 0; i < 10000; i++)
	{
		if (_server->IsConnected())
		{
			std::thread _task1(&Server::RecvAndSend1, _server);//
			std::thread _task2(&Server::RecvAndSend2, _server);//
			_task1.detach();
			_task2.detach();
			return true;
		}
		Sleep(1000);
	}
	return false;
}

static bool RecvAndSend(Server* _server)//在连接建立之后，以创建的Server对象为参数调用此函数， Server开始在两客户端之间进行数据交换
{
	std::thread _task(ServerRecvAndSend, _server);
	_task.detach();
	return true;
}

static bool SendMsgMod(Client* _client)//游戏中，进入发送信息状态时调用此函数， 用户可以输入聊天信息
{
	if (_client->IsConnected())
	{
		std::thread _task(&Client::SendMsg, _client);
		_task.detach();
		return true;
	}
	return false;
}

static bool RecvMsgMod(Client* _client)//仅仅在房间里进行聊天时使用
{
	if (_client->IsConnected())
	{
		std::thread _task(&Client::RecvToOrder, _client);
		_task.detach();
		return true;
	}
	return false;
}

static void SendMap(Client* _client)
{

}

static void SendStep(Server* _server)//房主开始游戏时调用
{
	std::thread _task(&Server::SendStep, _server);
	_task.join();
}

static void SendData(Client* _client, float _p1, float _p2, int _p3, int _p4, int _p5, int _p6)
{
	std::thread _task(&Client::SendData, _client, _p1, _p2, _p3, _p4, _p5, _p6);
	_task.detach();
}

/*static bool RecvInGame(Client* _client)//进入游戏后两边均调用此函数， 此后的SendData()所发信息均会在本地map中更新
{
	if (_client->IsConnected())
	{
		std::thread _task(&Client::RecvToMap, _client);
		_task.detach();
		return true;
	}
	return true;
}*/

#endif 