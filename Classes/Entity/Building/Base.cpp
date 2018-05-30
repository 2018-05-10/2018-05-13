#include"Classes/Entity/Building/Base.h"

Base::Base(Power* p,Mineral* m)
{
	_totalHP = 5000;
	_currentHP = 5000;
	_powerCost = 40;
	_mineralCost = 0;
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

Base::~Base() {}

bool Base::init()
{
	return true;
}

int Base::GetPowerCost()
{
	return _powerCost;
}
