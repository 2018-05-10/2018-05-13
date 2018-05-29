#include "Classes/Entity/Building/PowerStation.h"

PowerStation::PowerStation(Power* p, Mineral* m)
{
	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 0;
	_mineralCost = 100;
	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = true;
	p->Add(_powerProduce);
};
PowerStation::~PowerStation() {};

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