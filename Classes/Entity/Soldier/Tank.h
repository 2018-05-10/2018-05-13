#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;

class Tank :public Soldier
{
public:
	Tank();
	Tank(Mineral* m, SoldierManager* p);
	~Tank();
	bool init();

	CREATE_FUNC(Tank);
private:

};