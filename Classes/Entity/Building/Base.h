
#pragma once
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
class Base :public Building
{
public:
	Base(Power* p, Mineral* m);

	~Base();
	bool init();
	int GetPowerCost();

	//=========just for test===
	Base() = default;
	CREATE_FUNC(Base);
private:

};

