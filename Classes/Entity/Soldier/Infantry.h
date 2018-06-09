#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;
class SoldierManager;

class Infantry :public Soldier
{
public:
	Infantry();
	Infantry(Mineral *m, SoldierManager* p,int player);
	~Infantry();
	bool init();

	CREATE_FUNC(Infantry);
private:

};