
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
	int GetMineralProducePerSecond();    //ÿ������Ŀ�������
	bool init();

	CREATE_FUNC(Mine);
};