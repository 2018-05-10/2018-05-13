
#include "Mine.h"

Mine::Mine(Power* p,Mineral* m)
{
	_totalHP = 2000;
	_currentHP = 2000;
	_mineralCost = 50;
	_powerCost = 25;
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

Mine::~Mine() {}

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