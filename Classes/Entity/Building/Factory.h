#pragma once
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
USING_NS_CC;

class Factory :public Building
{
public:
	Factory();
	Factory(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);
	~Factory();
	bool init();
	int GetPowerCost();
	int GetMineralCost();

	CREATE_FUNC(Factory);
private:
};