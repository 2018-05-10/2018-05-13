#include "Tank.h"

Tank::Tank()
{
	_whatAmI = "Tank";
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
	_attackInterval = 1.0;

	Sprite* spr = Sprite::create("Tank.png");
	spr->setScale(2.0);
	this->BindSprite(spr);
} 

//Tank::Tank(Mineral* m, SoldierManager* p)
//{
//	_whatAmI = "Tank";
//	_totalHP = 300;
//	_currentHP = 300;
//	_attack = 150;
//	_speed = 3;
//	_mineralCost = 50;
//	_attackInterval = 1.0;
//
//	_pSoldierManager = p;
//	m->Cost(_mineralCost);
//}

Tank::~Tank() 
{
}

bool Tank::init()
{
	return true;
}