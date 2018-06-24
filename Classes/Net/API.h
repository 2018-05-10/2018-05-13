#ifndef _API_H_
#define _API_H_

#include "Server.h"
#include "Client.h"
#include <thread>
static bool RoomHolderClient(Client* _client, unsigned short _port)//���ù���
{
	_client->Create();
	_client->ConnectForHolder(_port);
	return true;
}

static bool OpenTheRoom(Server* _room, Client* _client, unsigned short _port)//�������ߵ��ã�_portȡ10000~60000(����11114)
{
	_room->Create();
	_room->Bind(_port);
	_room->Listen(2);
	std::thread _task(&Server::Broadcast, _room);//ʱ�䵽���̻߳��Զ��˳�
	_task.detach();
	RoomHolderClient(_client, _port);
	std::thread _taskOfAccept(&Server::AllAccept, _room);//�����������Ӻ��߳��˳�
	_taskOfAccept.detach();
	//_room->AllAccept();
	return true;
}

static bool RoomJoinerClient(Client* _client, unsigned short _port)//�����ߵ��ã�_portȡ��ͬ����
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

static bool RecvAndSend(Server* _server)//�����ӽ���֮���Դ�����Server����Ϊ�������ô˺����� Server��ʼ�����ͻ���֮��������ݽ���
{
	std::thread _task(ServerRecvAndSend, _server);
	_task.detach();
	return true;
}


static bool SendMsgMod(Client* _client)//��Ϸ�У����뷢����Ϣ״̬ʱ���ô˺����� �û���������������Ϣ
{
	if (_client->IsConnected())
	{
		std::thread _task(&Client::SendMsg, _client);
		_task.detach();
		return true;
	}
	return false;
}

static bool RecvMsgMod(Client* _client)//�����ڷ������������ʱʹ��
{
	if (_client->IsConnected())
	{
		std::thread _task(&Client::RecvMsg, _client);
		_task.detach();
		return true;
	}
	return false;
}

static bool RecvInGame(Client* _client)//������Ϸ�����߾����ô˺����� �˺��SendData()������Ϣ�����ڱ���map�и���
{
	if (_client->IsConnected())
	{
		std::thread _task(&Client::RecvToMap, _client);
		_task.detach();
		return true;
	}
	return true;
}



#endif 