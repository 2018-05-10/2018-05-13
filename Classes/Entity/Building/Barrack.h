<<<<<<< HEAD
#pragma once
#include "Building.h"
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Barrack :public Building
{
public:
	Barrack(Power* p, Mineral* m);
	~Barrack();
	bool init();
	int GetPowerCost();
	int GetMineralCost();
private:
=======
#pragma once
#include "Building.h"
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Barrack :public Building
{
public:
	Barrack(Power* p, Mineral* m);
	~Barrack();
	bool init();
	int GetPowerCost();
	int GetMineralCost();
private:
>>>>>>> 56e4016d2c955433aa3b7ab48b66f586a308c550
};