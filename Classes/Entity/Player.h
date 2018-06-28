#pragma once
#include<string>
#include"Net\API.h"
class Player
{

public:
	Player(Player const &) = delete;
	void operator=(Player const &) = delete;

	static Player* getInstance()
	{
		static Player INSTANCE;
		return &INSTANCE;
	}


	void setName(const std::string& name) { this->name = name; };
	std::string getName() const { return name; };
	bool getResult()const{ return _result; };
	void setResult(int i) { _result = i; };
	int getMapSize()const { return mapSize; };

	Client* client;
	Server* serve;
	bool isMaster = false;
	int isEnd = 0;
	int quitGame = 0;
private:
	Player() {};
	std::string name;
	bool _result=0;
	int mapSize = 75;
};
