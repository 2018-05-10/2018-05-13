#include "PowerStation.h"

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8


PowerStation::PowerStation(int id)
{
	_type=POWERSTATION;

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 0;
	_mineralCost = 100;
	_timeToBuild = 15;
	_player = 1;
	_ID = id;
	++enemyBuildingsID;

}

PowerStation::PowerStation(Power* p, Mineral* m,int player)
{
	_type = POWERSTATION;
	_pPower = p;

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 0;
	_mineralCost = 100;
	_timeToBuild = 15;
	_player = player;
	_ID = buildingsID;
	++buildingsID;

	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = false;
	
}

PowerStation::~PowerStation() 
{
	
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

