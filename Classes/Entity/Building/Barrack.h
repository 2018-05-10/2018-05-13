#pragma once
#include "Building.h"
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Barrack :public Building
{
public:
	Barrack(Power* p, Mineral* m);
	~Barrack();
	bool init();
	int GetPowerCost();
	int GetMineralCost();

	//=========just for test===
	Barrack() = default;
	CREATE_FUNC(Barrack);
private:
};