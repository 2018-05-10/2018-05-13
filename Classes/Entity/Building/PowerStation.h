#pragma once
#include "Building.h"

class PowerStation :public Building
{
public:
	PowerStation(int);
	PowerStation(Power* p, Mineral* m,int player);
	~PowerStation();
	bool init();
	int GetPowerProduce();
	int GetMineralCost();



private:
	const int _powerProduce = 50;     //能提供的电力
};