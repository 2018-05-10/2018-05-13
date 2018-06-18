#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <winsock.h>
#include <iostream>
#include <stdlib.h>
#include <map>
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
	bool Connect(unsigned short);
	bool IsConnected() const;
	char* GetIp() const;

	int Send(char*, int) const; //¼ò»¯send
	int Recv(char*, int) const; //¼ò»¯recv

	bool SendData(float, float, int, int, int) const;
	bool RecvData(float&, float&, int&, int&, int&);

	char* ChangeTo(float, float, int, int, int) const;
	void ChangeFrom(char*, float&, float&, int&, int&, int&) const; 

	bool SendMsg() const;

	std::map<int, unit> units;

	bool SendMap();
	bool RecvToMap();
};


#endif