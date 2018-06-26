#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdlib.h>
#include <WinSock2.h>
#include <Windows.h>
#include <winsock.h>
#include <iostream>
#include <string>
#pragma comment(lib,"ws2_32.lib")

class Server
{
private:
	SOCKET _serverSocket;
	SOCKET _clientSocket1;
	SOCKET _clientSocket2;
public:

	Server();
	~Server();

	bool Create();
	bool Bind(unsigned short);
	bool Listen(int) const;
	bool Accept(SOCKET&);
	bool AllAccept();

	void RecvAndSend1() const;
	void RecvAndSend2() const;

	bool IsConnected() const;
	char* GetIp() const;
	bool Broadcast();

	int _step;
	void SendStep();
};


#endif