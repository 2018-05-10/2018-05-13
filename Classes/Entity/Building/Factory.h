#pragma once
#include"cocos2d.h"
#include<queue>
#include"Building.h"

class Mineral;
class Power;
class Soldier;

class Factory :public Building
{
	friend class MenuLayr;
public:
	Factory();
	Factory(Power* p, Mineral* m,int player);
	~Factory();
	bool init();
	int GetPowerCost();
	int GetMineralCost();

	CREATE_FUNC(Factory);
private:
	std::queue<Soldier*> _buildingQueue;
};