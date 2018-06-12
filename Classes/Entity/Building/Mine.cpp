#include "Mine.h"

Mine::Mine()
{
	_whatAmI = "Mine";
	
	_totalHP = 2000;
	_currentHP = 2000;
	_mineralCost = 50;
	_powerCost = 25;
	_timeToBuild = 15;
	_player = 1;
	++buildingsID;

	Sprite* spr = Sprite::create("Building/Mine.png");
	this->BindSprite(spr);
}

Mine::Mine(Power* p,Mineral* m, BuildingManager* pManagerItBelongsTo,int player)
{
	_whatAmI = "Mine";
	_pPower = p;
	_pManager = pManagerItBelongsTo;

	_totalHP = 2000;
	_currentHP = 2000;
	_mineralCost = 50;
	_powerCost = 25;
	_timeToBuild = 15;
	_player = player;
	_buildingID = buildingsID;
	++buildingsID;

	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = false;
}

Mine::~Mine() 
{
	_pPower->Free(_powerCost);
}

int Mine::GetMineralCost()
{
	return _mineralCost;
}

int Mine::GetPowerCost()
{
	return _powerCost;
}

int Mine::GetMineralProducePerSecond()
{
	return _mineralProducePerSecond;
}

bool Mine::init()
{
	return true;
}