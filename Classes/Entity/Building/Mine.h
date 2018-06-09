
#pragma once
#include "Building.h"
USING_NS_CC;

class Mine :public Building
{
public:
	Mine();
	Mine(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo,int player);
	~Mine();
	int GetMineralCost();
	int GetPowerCost();
	int GetMineralProducePerSecond();    //每秒产出的矿物数量
	bool init();

	CREATE_FUNC(Mine);
};