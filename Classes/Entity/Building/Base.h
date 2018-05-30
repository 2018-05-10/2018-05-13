#pragma once
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
class Base :public Building
{
public:
	Base(Power* p, Mineral* m);
	Base() = default;
	~Base();
	bool init();
	int GetPowerCost();

	CREATE_FUNC(Base);
private:

};
