#include "Base.h"

Base::Base(BuildingManager* pManagerItBelongsTo)
{
	_whatAmI = "Base";

	_totalHP = 5000;
	_currentHP = 5000;
	_powerCost = 40;
	_mineralCost = 0;
	_timeToBuild = 10;
	_player = 1; 
	_pManager = pManagerItBelongsTo;
	++buildingsID;

}

Base::Base(Power* p,Mineral* m, BuildingManager* pManagerItBelongsTo,int player)
{
	_whatAmI = "Base";
	_pPower = p;
	_pMineral = m;
	_pManager = pManagerItBelongsTo;

	_totalHP = 5000;
	_currentHP = 5000;
	_powerCost = 40;
	_mineralCost = 0;
	_timeToBuild = 10;
	_player = player;
	_buildingID=buildingsID++;


	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = false;

}

Base::~Base() 
{
	if (!_player)
	{
		_pPower->Free(_powerCost);
	}
}

bool Base::init()
{
	return true;
}

int Base::GetPowerCost()
{
	return _powerCost;
}

