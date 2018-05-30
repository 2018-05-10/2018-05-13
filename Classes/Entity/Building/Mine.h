
#pragma once
#include "Building.h"
USING_NS_CC;

class Mine :public Building
{
public:
	Mine(Power* p,Mineral* m);
	~Mine();
	int GetMineralCost();
	int GetPowerCost();
	int GetMineralProducePerSecond();
	bool init();

	
private:
	const int _mineralProducePerSecond = 5;

};