#include "Dog.h"
#include"Resource/Mineral.h"

Dog::Dog()
{
	_whatAmI = "Dog";
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;

}

Dog::Dog(Mineral* m ,SoldierManager* p,int player)
{
	_whatAmI = "Dog";
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;
	_player = player;

	_pSoldierManager = p;
	m->Cost(_mineralCost);
}

Dog::~Dog() {}

bool Dog::init()
{
	return true;
}