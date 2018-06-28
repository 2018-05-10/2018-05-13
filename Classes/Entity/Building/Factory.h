#pragma once
#include"cocos2d.h"
#include<queue>
#include"Building.h"

class Mineral;
class Power;
class Soldier;

class Factory :public Building
{
	friend class MenuLayer;
public:
	Factory(int);
	Factory(Power* p, Mineral* m,int player);
	~Factory();
	bool init();
	int GetPowerCost();
	int GetMineralCost();
	void FactoryUpdate(float dt);


private:
	std::queue<char*> _buildingList;
};