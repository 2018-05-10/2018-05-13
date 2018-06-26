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

	Client* client;
	Server* serve;
	bool isMaster = false;
private:
	Player() {};
	std::string name;

};
