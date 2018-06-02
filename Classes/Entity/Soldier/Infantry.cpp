#include "Infantry.h"

Infantry::Infantry()
{
	_whatAmI = "Infantry";
	_totalHP = 150;
	_currentHP = 150;
	_attack = 50;
	_speed = 1;
	_mineralCost = 20;
	_attackInterval = 0.3;


	Sprite* spr = Sprite::create("Infantry.png");
	this->BindSprite(spr);
}

//Infantry::Infantry(Mineral *m, SoldierManager* p)
//{
//	_whatAmI = "Infantry";
//	_totalHP = 150;
//	_currentHP = 150;
//	_attack = 50;
//	_speed = 1;
//	_mineralCost = 20;
//	_attackInterval = 0.3;
//
//	_pSoldierManager = p;
//	m->Cost(_mineralCost);
//}

Infantry::~Infantry() {}

bool Infantry::init()
{
	return true;
}