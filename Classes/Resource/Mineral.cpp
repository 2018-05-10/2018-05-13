#include "Mineral.h"

Mineral::Mineral()
{
	_currentVal = 150;
}
Mineral::~Mineral(){}

bool Mineral::init()
{
	return true;
}

int Mineral::GetCurrentVal()
{
	return _currentVal;
}

void Mineral::Cost(int val)
{
	_currentVal -= val;
}

void Mineral::Add(int val)
{
	_currentVal += val;
}