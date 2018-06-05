#include "Factory.h"

Factory::Factory()
{
	_whatAmI = "Factory";
	
	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 15;
	++buildingsID;

	Sprite* spr = Sprite::create("Building/Factory.png");
	this->BindSprite(spr);
}

Factory::Factory(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo)
{
	_whatAmI = "Factory";
	_pPower = p;
	_pManager = pManagerItBelongsTo;

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 15;
	++buildingsID;

	m->Cost(_mineralCost);
	p->Use(_powerCost);
	if (p->GetUsedVal() > p->GetTotalVal())
	{
		_isWorking = false;
	}
	else
	{
		_isWorking = true;
	}
}

Factory::~Factory()
{
	/*_pPower->Free(_powerCost);*/
}

bool Factory::init()
{
	return true;
}

int Factory::GetPowerCost()
{
	return _powerCost;
}

int Factory::GetMineralCost()
{
	return _mineralCost;
}