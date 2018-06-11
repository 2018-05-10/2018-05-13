#pragma once
#include "Building.h"

class PowerStation :public Building
{
public:
	PowerStation();
	PowerStation(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);
	~PowerStation();
	bool init();
	int GetPowerProduce();
	int GetMineralCost();


	CREATE_FUNC(PowerStation);
private:
	const int _powerProduce = 50;     //���ṩ�ĵ���
};