#include "Server.h"

Server::Server()
{
	WSADATA _data;
	WSAStartup(MAKEWORD(2, 2), &_data);
	_serverSocket = 0;
}

Server::Server(SOCKET _socket)
{
	WSADATA _data;
	WSAStartup(MAKEWORD(2, 2), &_data);
	_serverSocket = _socket;
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
	_addr.sin_addr.S_un.S_addr = INADDR_ANY;
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
	return true;
}

void Server::RecvAndSend1() const
{
	while (1)
	{
		char _str[1024] = { 0 };
		int _judge = recv(_clientSocket1, _str, sizeof(_str), 0);
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
		int _judge = recv(_clientSocket2, _str, sizeof(_str), 0);
		if (_judge <= 0)
		{
			break;
		}
		send(_clientSocket1, _str, sizeof(_str), 0);
	}
}

bool Server::IsConnected() const
{
	return (_serverSocket == 0 || _clientSocket1 == 0 || _clientSocket2 == 0) ? false : true;
}