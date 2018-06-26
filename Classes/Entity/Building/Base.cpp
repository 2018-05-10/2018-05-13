#include "Base.h"

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8

Base::Base()
{
	_type = BASE;

	_totalHP = 5000;
	_currentHP = 5000;
	_powerCost = 40;
	_mineralCost = 0;
	_timeToBuild = 10;
	_player = 1; 
	_ID = enemyBuildingsID;
	++enemyBuildingsID;

}

Base::Base(Power* p,Mineral* m,int player)
{
	_type = BASE;
	_pPower = p;
	_pMineral = m;


	_totalHP = 5000;
	_currentHP = 5000;
	_powerCost = 40;
	_mineralCost = 0;
	_timeToBuild = 10;
	_player = player;
	_ID=buildingsID++;


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

