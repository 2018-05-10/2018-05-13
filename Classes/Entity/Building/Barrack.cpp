<<<<<<< HEAD
#include "Barrack.h"

Barrack::Barrack(Power* p, Mineral* m)
{
	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
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

Barrack::~Barrack(){}

bool Barrack::init()
{
	return true;
}

int Barrack::GetPowerCost()
{
	return _powerCost;
}

int Barrack::GetMineralCost()
{
	return _mineralCost;
=======
#include "Barrack.h"

Barrack::Barrack(Power* p, Mineral* m)
{
	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
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

Barrack::~Barrack(){}

bool Barrack::init()
{
	return true;
}

int Barrack::GetPowerCost()
{
	return _powerCost;
}

int Barrack::GetMineralCost()
{
	return _mineralCost;
>>>>>>> 56e4016d2c955433aa3b7ab48b66f586a308c550
}