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
}