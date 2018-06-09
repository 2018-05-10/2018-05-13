#include "Tank.h"
#include "Resource/Mineral.h"
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

Tank::Tank(Mineral* m, SoldierManager* p,int player)
{
	_whatAmI = "Tank";
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
	_attackInterval = 1.0;
	_player = player;

	_pSoldierManager = p;
	m->Cost(_mineralCost);
}

Tank::~Tank() 
{
}

bool Tank::init()
{
	return true;
}