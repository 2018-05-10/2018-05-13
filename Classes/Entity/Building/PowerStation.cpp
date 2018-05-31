#include "Heads.h"

PowerStation::PowerStation()
{
	_whatAmI = "PowerStation";

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 0;
	_mineralCost = 100;
	_timeToBuild = 15;

	Sprite* spr = Sprite::create("PowerStation.png");
	this->BindSprite(spr);
}

PowerStation::PowerStation(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo)
{
	_whatAmI = "PowerStation";
	_pPower = p;
	_pManager = pManagerItBelongsTo;

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 0;
	_mineralCost = 100;
	_timeToBuild = 15;

	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = true;
	p->Add(_powerProduce);
}

PowerStation::~PowerStation() 
{
	_pPower->Reduce(_powerProduce);
}

bool PowerStation::init()
{
	return true;
}

int PowerStation::GetPowerProduce()
{
	return _powerProduce;
}

int PowerStation::GetMineralCost()
{
	return _mineralCost;
}