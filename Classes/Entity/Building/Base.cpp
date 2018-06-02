#include "Base.h"

Base::Base()
{
	_whatAmI = "Base";

	_totalHP = 5000;
	_currentHP = 5000;
	_powerCost = 40;
	_mineralCost = 0;
	_timeToBuild = 0;
	_buildingID = buildingsID++;

	Sprite* spr = Sprite::create("Building/Base.png");
	this->BindSprite(spr);
}

Base::Base(Power* p,Mineral* m, BuildingManager* pManagerItBelongsTo)
{
	_whatAmI = "Base";
	_pPower = p;
	_pManager = pManagerItBelongsTo;

	_totalHP = 5000;
	_currentHP = 5000;
	_powerCost = 40;
	_mineralCost = 0;
	_timeToBuild = 0;

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

Base::~Base() 
{
	/*_pPower->Free(_powerCost);*/
}

bool Base::init()
{
	return true;
}

int Base::GetPowerCost()
{
	return _powerCost;
}
