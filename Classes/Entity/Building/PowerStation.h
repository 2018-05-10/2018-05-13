#pragma once
#include "Building.h"

class PowerStation :public Building 
{
public:
	PowerStation(Power* p, Mineral* m);
	~PowerStation();
	bool init();
	int GetPowerProduce();
	int GetMineralCost();
private:
	const int _powerProduce = 50;

};