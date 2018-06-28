
#pragma once
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
class Base :public Building
{
public:
	Base(int);
	Base(Power* p, Mineral* m,int player);
	~Base();
	bool init();
	int GetPowerCost();


};

