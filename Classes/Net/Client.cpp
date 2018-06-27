#include "Client.h"
#include "Entity\Player.h"
Client::Client()//不用关心
{
	WSADATA _data;
	WSAStartup(MAKEWORD(2, 2), &_data);
	_clientSocket = 0;
	_step = 0;
	_isReady = 0;
}

Client::~Client()//不用关心
{
	closesocket(_clientSocket);
	_orders.clear();
	_chatMsgRecv.clear();
	_chatMsgSend.clear();
}

bool Client::Create()//不用关心
{
	_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_clientSocket == INVALID_SOCKET)
	{
		return false;
	}
	return true;
}

bool Client::ConnectForHolder(unsigned short _port)//不用关心
{
	char* _ip = GetIp();
	sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.S_un.S_addr = inet_addr(_ip);
	connect(_clientSocket, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
	return true;
}

bool Client::ConnectForJoiner(unsigned short _port)//不用关心
{
	char* _ip = RecvBroadcast();
	sockaddr_in _addr;
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(_port);
	_addr.sin_addr.S_un.S_addr = inet_addr(_ip);
	connect(_clientSocket, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
	_step++;
	delete[] _ip;
	return true;
}

bool Client::IsConnected() const//不用关心
{
	return _clientSocket != 0 ? true : false;
}

char* Client::GetIp() const//不用关心
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

int Client::Send(char* _buffer, int _len) const//不用关心
{
	return (send(_clientSocket, _buffer, _len, 0));
}

int Client::Recv(char* _buffer, int _len) const//不用关心
{
	return (recv(_clientSocket, _buffer, _len, 0));
}

bool Client::SendData(float _p1, float _p2, int _p3, int _p4, int _p5, int _p6) const//在单位的属性有改变时均需调用此函数来发送新的属性值
{
	char _str[100] = { 0 };
	int _judge = 0;
	char* _str2 = ChangeTo(_p1, _p2, _p3, _p4, _p5, _p6);
	for (int i = 0; i < 100; i++)
	{
		_str[i] = _str2[i];
	}
	_str[96] = 'd';
	_str[97] = 'd';
	_str[98] = 'd';
	_judge = Send(_str, 100);
	if (_judge <= 0)
	{
		return false;
	}
	
	return true;
}

bool Client::RecvData(float &_p1, float &_p2, int &_p3, int &_p4, int &_p5, int &_p6)//游戏中接受数据，如果收到对话信息则输出到聊天层中
{
	char* _str = new char[100];
	int _judge = 0;
	Recv(_str, 100);
	std::string _s = _str;
	if (_s == "_step++")
	{
		_step++;
		delete[] _str;
		return true;
	}
	if (_s == "_getReady")
	{
		_isReady = 1;
		delete[] _str;
		return true;
	}
	if (_s == "_cancelReady")
	{
		_isReady = 0;
		delete[] _str;
		return true;
	}
	if (_s == "_cancelReady")
	{
		_isReady = 0;
		delete[] _str;
		return true;
	}
	else if(strlen(_str) == 99 && _str[96] == 'd' && _str[97] == 'd' && _str[98] == 'd')
	{
		ChangeFrom(_str, _p1, _p2, _p3, _p4, _p5, _p6);
		delete[] _str;
		return true;
	}
	else
	{
		std::string _chat = _str;
		_chatMsgRecv.push_back(_chat);//将对话信息输出
		delete[] _str;
		return true;
	}
}

char* Client::ChangeTo(float _p1, float _p2, int _p3, int _p4, int _p5, int _p6) const//不用关心
{
	char _str[1024] = { 0 };
	sprintf(_str, "%-16f%-16f%-16d%-16d%-16d%-16d", _p1, _p2, _p3, _p4, _p5, _p6);
	return _str;
}

void Client::ChangeFrom(char* _str, float &_p1, float &_p2, int &_p3, int &_p4, int &_p5, int &_p6) const//不用关心
{
	for (int i = 0; i < 6; i++)
	{
		char _s[16] = { 0 };
		for (int j = 0; j < 16; j++)
		{
			_s[j] = _str[j + i * 16];
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
		case 5:
			_p6 = atoi(_s);
			continue;
		}
	}
}

bool Client::SendMsg()//SendMsgMod所开的线程函数
{
	const char* _myName = new char[100];
	_myName = _playerName.c_str();
	send(_clientSocket, _myName, 100, 0);

	while (1)
	{
		if (Player::getInstance()->isEnd >= 5000)
		{
			break;
		}
		Sleep(50);
		std::vector<std::string>::iterator _it = _chatMsgSend.begin();
		char _str[100] = { 0 };
		int _judge = 0;
		for (1; _it != _chatMsgSend.end(); _it++)
		{
			strcpy(_str, (*_it).c_str());
			if (_str[0] != '\0')
			{
				_judge = Send(_str, 100);
				1;
			}
		}
		if (Player::getInstance()->isEnd >= 5000)
		{
			break;
		}
		_chatMsgSend.clear();
	}
	//delete[] _myName;
	return true;
}

/*bool Client::RecvMsg()///在房间中使用，RecvMsgMod所开的线程函数
{
	while (1)
	{
		char _str[1024] = { 0 };
		Recv(_str, 1024);
		if (_str[0] != '\0')
		{
			std::string _chat = _str;
			_chatMsgRecv.push_back(_chat);//存在vector里了，输出之后清空vector
			//std::cout << _str << std::endl;
		}
	}
}*/

bool Client::RecvToOrder()//RecvMsgMod所开的线程函数，功能整合到这个函数了
{
	char* _opName = new char[100];
	recv(_clientSocket, _opName, 100, 0);
	_opponentName = _opName;

	float _x = 0;
	float _y = 0;
	int _goal = 0;
	int _id = 0;
	int _kind = 0;
	int _func = 0;
	while (1)
	{
		if (Player::getInstance()->isEnd >= 5000)
		{
			break;
		}
		RecvData(_x, _y, _goal, _id, _kind, _func);
		int i = Player::getInstance()->isEnd;
		if (Player::getInstance()->isEnd >= 5000)
		{
			break;
		}
		unit _u =
		{
			_x, _y, _goal, _id, _kind, _func
		};
		
		
		_orders.push_back(_u);
		
	}
	//delete[] _opName;
	return true;
}

/*bool Client::RecvToMap()//RecvMsgMod所开的线程函数，功能整合到这个函数了
{
	char* _opName = new char[1024];
	recv(_clientSocket, _opName, 1024, 0);
	_opponentName = _opName;

	float _x = 0;
	float _y = 0;
	int _goal = 0;
	int _id = 0;
	int _judge = 0;
	while (1)
	{
		RecvData(_x, _y, _goal, _id, _judge);
		_units[_id]._x = _x;
		_units[_id]._y = _y;
		_units[_id]._goal = _goal;
		_units[_id]._id = _id;
		_units[_id]._judge = _judge;
	}
	//delete[] _opName;
	return true;
}*/

/*bool Client::SendMap()
{
	return true;
}*/

char* Client::RecvBroadcast()// 不用关心
{
	WSADATA _data;
	WORD _v = MAKEWORD(2, 2);
	WSAStartup(_v, &_data);
	SOCKET _s = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN _addr, _sender;
	int _senderSize = sizeof(_sender);
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(11114);
	char* _ip = GetIp();

	_addr.sin_addr.s_addr = inet_addr(_ip);
	bind(_s, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr));
	bool _optval = true;
	setsockopt(_s, SOL_SOCKET, SO_BROADCAST, (char*)&_optval, sizeof(bool));
	char* _opip = new char[1000];
	while (1)
	{
		int _judge = recvfrom(_s, _opip, 1000, 0, reinterpret_cast<sockaddr*>(&_sender), &_senderSize);
		if (_judge > 0)
		{
			return _opip;
		}
	}
	delete[] _opip;
	return false;
}