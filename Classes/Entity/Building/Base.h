
#pragma once
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
class Base :public Building
{
public:
	Base();
	Base(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo,int player);
	~Base();
	bool init();
	int GetPowerCost();

	CREATE_FUNC(Base);
};

