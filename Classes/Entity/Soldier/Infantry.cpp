#include "Infantry.h"

Infantry::Infantry()
{
	_totalHP = 150;
	_currentHP = 150;
	_attack = 50;
	_speed = 1;
	_mineralCost = 20;
}

Infantry::~Infantry() {}

bool Infantry::init()
{
	return true;
}