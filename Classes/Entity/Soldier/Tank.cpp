<<<<<<< HEAD
#include "Tank.h"

Tank::Tank()
{
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
}

Tank::~Tank() {}

bool Tank::init()
{
	return true;
=======
#include "Tank.h"

Tank::Tank()
{
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
}

Tank::~Tank() {}

bool Tank::init()
{
	return true;
>>>>>>> 56e4016d2c955433aa3b7ab48b66f586a308c550
}