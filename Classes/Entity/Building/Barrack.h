#pragma once
#include "Building.h"
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Barrack :public Building
{
public:
	Barrack();
	Barrack(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);       //传入的三个变量分别是为了修改相应的电力，矿产，以及确定该对象在哪个管理类的管理之下
	~Barrack();
	bool init();
	int GetPowerCost();     //所消耗的电力
	int GetMineralCost();       //所消耗的矿物
	

	CREATE_FUNC(Barrack);
private:
};