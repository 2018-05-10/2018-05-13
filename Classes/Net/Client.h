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
#include <queue>
#include <deque>
#pragma comment(lib,"ws2_32.lib")

typedef struct unit
{
	float _x;
	float _y;
	int _goal;
	int _id;
	int _kind;
	int _func;
};

class Client
{
private:
	SOCKET _clientSocket;
public:
	Client();
	~Client();

	bool Create();
	bool ConnectForHolder(unsigned short);
	bool ConnectForJoiner(unsigned short);
	bool IsConnected() const;
	char* GetIp() const;

	int Send(char*, int) const;
	int Recv(char*, int) const;

	bool SendData(float, float, int, int, int, int) const;
	bool RecvData(float&, float&, int&, int&, int&, int&);

	char* ChangeTo(float, float, int, int, int, int) const;
	void ChangeFrom(char*, float&, float&, int&, int&, int&, int&) const;

	bool SendMsg();
	//bool RecvMsg();

	bool RecvToOrder();
	//bool RecvToMap();
	//bool SendMap();

	char* RecvBroadcast();;

	//std::map<int, unit> _units;
	std::deque<unit> _orders;


	std::vector<std::string> _chatMsgSend;
	std::vector<std::string> _chatMsgRecv;

	std::string _playerName;
	std::string _opponentName;

	int _step;
	bool _isReady;
};


#endif