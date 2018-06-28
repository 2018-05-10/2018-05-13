#include "Mine.h"

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8

Mine::Mine(int id)
{
	_type = MINE;
	
	_totalHP = 2000;
	_currentHP = 2000;
	_mineralCost = 50;
	_powerCost = 25;
	_timeToBuild = 15;
	_player = 1;
	_ID = id;
	++enemyBuildingsID;

}

Mine::Mine(Power* p,Mineral* m,int player)
{
	_type = MINE;
	_pPower = p;


	_totalHP = 2000;
	_currentHP = 2000;
	_mineralCost = 50;
	_powerCost = 25;
	_timeToBuild = 15;
	_player = player;
	_ID = buildingsID;
	++buildingsID;

	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = false;
}

Mine::~Mine() 
{
	if (!_player)
	{
		_pPower->Free(_powerCost);
	}
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