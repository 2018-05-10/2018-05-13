
#pragma once
#include "Building.h"
USING_NS_CC;

class Mine :public Building
{
public:
	Mine(int);
	Mine(Power* p, Mineral* m,int player);
	~Mine();
	int GetMineralCost();
	int GetPowerCost();
	int GetMineralProducePerSecond();    //ÿ������Ŀ�������
	bool init();

};