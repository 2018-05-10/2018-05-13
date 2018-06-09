#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;

class Dog :public Soldier
{
public:
	Dog();
	Dog(Mineral* m, SoldierManager* p,int player);
	~Dog();
	bool init();

	CREATE_FUNC(Dog);
private:
};