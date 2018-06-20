#include "Client.h"

Client::Client()
{
	WSADATA _data;
	WSAStartup(MAKEWORD(2, 2), &_data);
	_clientSocket = 0;
}

Client::Client(SOCKET _socket)
{
	WSADATA _data;
	WSAStartup(MAKEWORD(2, 2), &_data);
	_clientSocket = _socket;
}

Client::~Client()
{
	closesocket(_clientSocket);
	units.clear();
}

bool Client::Create()
{
	_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_clientSocket == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool Client::Connect(unsigned short _port)
{
	char* _ip = GetIp();
	sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_addr.S_un.S_addr = inet_addr(_ip);
	_addr.sin_port = htons(_port);

	int _retryTimes = 0;
	int _judge = -1;
	for (1;_judge == -1 && _retryTimes <= 10; _retryTimes++)
	{
		_judge = connect(_clientSocket, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
		Sleep(50);
	}
	
	if (_judge == -1)
	{
		return false;
	}
	return true;
}

bool Client::IsConnected() const
{
	return _clientSocket == 0 ? false : true;
}

char* Client::GetIp() const
{
	WSADATA _data;
	int _judge = WSAStartup(MAKEWORD(2, 0), &_data);
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

int Client::Send(char* _buffer, int _len) const
{
	return (send(_clientSocket, _buffer, _len, 0));
}

int Client::Recv(char* _buffer, int _len) const
{
	return (recv(_clientSocket, _buffer, _len, 0));
}

bool Client::SendData(float _p1, float _p2, int _p3, int _p4, int _p5) const
{
	char* _str = new char[42];
	int _judge = 0;
	_str = ChangeTo(_p1, _p2, _p3, _p4, _p5);
	_str[40] = 'd';
	_str[41] = '\0';
	if (_str[0] != '\0')
	{
		_judge = Send(_str, 41);
	}
	if (_judge <= 0)
	{
		return false;
	}
	return true;
}

bool Client::RecvData(float _p1, float _p2, int _p3, int _p4, int _p5)
{
	char* _str = new char[1024];
	int _judge = 0;
	Recv(_str, 1024);
	if (_str[strlen(_str) - 1] == 'm')
	{
		_str[strlen(_str) - 1] = '\0';
		// 输出到对话层
		return true;
	}
	else
	{
		ChangeFrom(_str, _p1, _p2, _p3, _p4, _p5);
		return true;
	}
}

char* Client::ChangeTo(float _p1, float _p2, int _p3, int _p4, int _p5) const
{
	char _str[41] = { 0 };
	sprintf_s(_str, "%-8f%-8f%-8d%-8d%-8d", _p1, _p2, _p3, _p4, _p5);
	return _str;
}

void Client::ChangeFrom(char* _str,float &_p1, float &_p2, int &_p3, int&_p4, int &_p5) const
{
	for (int i = 0; i < 5; i++)
	{
		char _s[8] = { 0 };
		for (int j = 0; j < 8; j++)
		{
			_s[j] = _str[j + i * 8];
		}
		switch (i)
		{
		case 0:
			_p1 = atof(_s);
			continue;
		case 1:
			_p2 = atof(_s);
			continue;
		case 2:
			_p3 = atoi(_s);
			continue;
		case 3:
			_p4 = atoi(_s);
			continue;
		case 4:
			_p5 = atoi(_s);
			continue;
		}
	}
}

bool Client::SendMsg() const
{
	while (1)
	{
		char _str[1024] = { 0 };
		int _judge = 0;
		std::cin >> _str;
		if (_str[0] != '\0')
		{
			_str[strlen(_str) + 1] = '\0';
			_str[strlen(_str)] = 'm';
			_judge = Send(_str, 1024);
		}
		else
		{
			break;
		}
		if (_judge <= 0)
		{
			return false;
		}
	}
	return true;
}

bool Client::RecvToMap()
{
	float _x;
	float _y;
	int _life;
	int _goal;
	int _id;
	while (1)
	{
		RecvData(_x, _y, _life, _goal, _id);
		units[_id]._x = _x;
		units[_id]._y = _y;
		units[_id]._life = _life;
		units[_id]._goal = _goal;
		units[_id]._id = _id;
		units[_id]._judge = 1;
	}
	return true;
}