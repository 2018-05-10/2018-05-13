
#include "Classes/Resource/Power.h"

Power::Power()
{
	_totalVal = 50;
	_usedVal = 0;
	_availableVal = 50;
}
Power::~Power(){}

int Power::GetTotalVal()
{
	return _totalVal;
}

int Power::GetUsedVal()
{
	return _usedVal;
}

int Power::GetAvailableVal()
{
	return _availableVal;
}

void Power::Use(int val)
{
	_usedVal += val;
	_availableVal = _totalVal - _usedVal;
}

void Power::Add(int val)
{
	_totalVal += val;
}

void Power::Reduce(int val)
{
	_totalVal -= val;
}