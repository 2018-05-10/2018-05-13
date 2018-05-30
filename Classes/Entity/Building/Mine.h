<<<<<<< HEAD
#pragma once
#include "Building.h"
USING_NS_CC;

class Mine :public Building
{
public:
	Mine(Power* p,Mineral* m);
	~Mine();
	int GetMineralCost();
	int GetPowerCost();
	int GetMineralProducePerSecond();
	bool init();
private:
	const int _mineralProducePerSecond = 5;
=======
#pragma once
#include "Building.h"
USING_NS_CC;

class Mine :public Building
{
public:
	Mine(Power* p,Mineral* m);
	~Mine();
	int GetMineralCost();
	int GetPowerCost();
	int GetMineralProducePerSecond();
	bool init();
private:
	const int _mineralProducePerSecond = 5;
>>>>>>> 56e4016d2c955433aa3b7ab48b66f586a308c550
};