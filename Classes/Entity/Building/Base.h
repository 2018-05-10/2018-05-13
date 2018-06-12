
#pragma once
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
class Base :public Building
{
public:
	Base(BuildingManager* pManagerItBelongsTo);
	Base(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo,int player);
	~Base();
	bool init();
	int GetPowerCost();


};

