#include "Server.h"

Server::Server()
{
	WSADATA _data;
	WSAStartup(MAKEWORD(2, 2), &_data);
	_serverSocket = 0;
	_clientSocket1 = 0;
	_clientSocket2 = 0;
	_step = 0;
}

Server::~Server()
{
	closesocket(_serverSocket);
	closesocket(_clientSocket1);
	closesocket(_clientSocket2);
}

bool Server::Create()
{
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool Server::Bind(unsigned short _port)
{
	sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	_addr.sin_port = htons(_port);

	int _judge = bind(_serverSocket, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
	if (_judge == -1)
	{
		return false;
	}
	return true;
}

bool Server::Listen(int _num) const
{
	int _judge = listen(_serverSocket, _num);
	if (_judge == -1)
	{
		return false;
	}
	return true;
}

bool Server::Accept(SOCKET &_client)
{
	sockaddr_in _addr;
	int _size = sizeof(_addr);
	SOCKET _sock = accept(_serverSocket, reinterpret_cast<sockaddr*>(&_addr), &_size);
	if (_sock == -1)
	{
		return false;
	}
	_client = _sock;
	return true;
}

bool Server::AllAccept()
{
	Accept(_clientSocket1);
	Accept(_clientSocket2);
	_step++;
	return true;
}

void Server::RecvAndSend1() const
{
	while (1)
	{
		char _str[1024] = { 0 };
		int _judge = recv(_clientSocket1, _str, 1024, 0);
		if (_judge <= 0)
		{
			break;
		}
		send(_clientSocket2, _str, sizeof(_str), 0);
	}
}

void Server::RecvAndSend2() const
{
	while (1)
	{
		char _str[1024] = { 0 };
		int _judge = recv(_clientSocket2, _str, 1024, 0);
		if (_judge <= 0)
		{
			break;
		}
		send(_clientSocket1, _str, sizeof(_str), 0);
	}
}

bool Server::IsConnected() const
{
	return ((_serverSocket != 0 && _clientSocket1 != 0 && _clientSocket2 != 0) ? true : false);
}

char* Server::GetIp() const
{
	WSADATA _data;
	int _judge = WSAStartup(MAKEWORD(2, 2), &_data);
	if (_judge != 0)
	{
		return false;
	}

	char _hostname[1024] = { 0 };
	_judge = gethostname(_hostname, sizeof(_hostname));
	if (_judge == -1)
	{
		return false;
	}

	HOSTENT* _host = gethostbyname(_hostname);
	if (_host == NULL)
	{
		return false;
	}

	char* _ip;
	_ip = inet_ntoa(*((in_addr*)(*(_host->h_addr_list))));
	_ip = inet_ntoa(*(reinterpret_cast<in_addr*>(*(_host->h_addr_list))));
	return _ip;
}

bool Server::Broadcast()
{
	WSADATA _data;
	WORD _v = MAKEWORD(2, 2);
	WSAStartup(_v, &_data);
	SOCKET _s = socket(AF_INET, SOCK_DGRAM, 0);
	bool _optval = true;
	setsockopt(_s, SOL_SOCKET, SO_BROADCAST, (char*)&_optval, sizeof(bool));
	SOCKADDR_IN _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(11114);
	_addr.sin_addr.s_addr = INADDR_BROADCAST;
	char* _ip = new char[500];
	_ip = GetIp();
	for (int i = 0; i < 10000; i++)
	{
		sendto(_s, _ip, 500, 0, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
		Sleep(1000);
		if (_step == 1)
		{
			break;
		}
	}
	//delete[] _ip;
	return true;
}

void Server::SendStep()
{
	_step++;
	send(_clientSocket2, "_step++", 8, 0);
}