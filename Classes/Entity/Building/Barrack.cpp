#include "Barrack.h"

Barrack::Barrack()
{
	_whatAmI = "Barrack";

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 15;
	++buildingsID;

	Sprite* spr = Sprite::create("Building/Barrack.png");
	this->BindSprite(spr);
}

Barrack::Barrack(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo)
{
	_whatAmI = "Barrack";
	_pPower = p;
	_pManager = pManagerItBelongsTo;

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 15;
	++buildingsID;

	Sprite* spr = Sprite::create("Barrack_gray.png");
	this->BindSprite(spr);

	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = false;
	
}

Barrack::~Barrack()
{
	/*_pPower->Free(_powerCost);*/
}

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
}