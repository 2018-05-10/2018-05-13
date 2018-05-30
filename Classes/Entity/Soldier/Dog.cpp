#include "Dog.h"

Dog::Dog()
{
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
}

Dog::~Dog() {}

bool Dog::init()
{
	return true;
}