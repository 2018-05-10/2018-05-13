#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <WinSock2.h>
#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include <list>
#pragma comment(lib,"ws2_32.lib")

typedef struct unit
{
	float _x;
	float _y;
	int _life;
	int _goal;
	int _id;
	int _judge;
};

class Client
{
private:
	SOCKET _clientSocket;
public:
	Client();
	Client(SOCKET);
	~Client();

	bool Create();
	bool ConnectForHolder(unsigned short);
	bool ConnectForJoiner(unsigned short);
	bool IsConnected() const;
	char* GetIp() const;

	int Send(char*, int) const; //¼ò»¯send
	int Recv(char*, int) const; //¼ò»¯recv

	bool SendData(float, float, int, int, int, int) const;
	bool RecvData(float&, float&, int&, int&, int&, int&);

	char* ChangeTo(float, float, int, int, int, int) const;
	void ChangeFrom(char*, float&, float&, int&, int&, int&, int&) const; 

	bool SendMsg();
	bool RecvMsg();

	bool RecvToMap();

	char* RecvBroadcast();;

	std::map<int, unit> _units;

	std::vector<std::string> _chatMsgRecv;
	std::vector<std::string> _chatMsgSend;
};


#endif