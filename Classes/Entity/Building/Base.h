#pragma once
#include "Building.h"

class Base :public Building
{
public:
	Base(Power* p, Mineral* m);
	~Base();
	bool init();
	int GetPowerCost();
private:

};
