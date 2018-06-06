#include "Power.h"
Power::Power()
{
	_totalVal = 99999;
	_usedVal = 0;
	_availableVal = 99999;
}
Power::~Power(){}

bool Power::init()
{
	return true;
}

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

void Power::Free(int val)
{
	_usedVal -= val;
	_availableVal = _totalVal - _usedVal;
}

void Power::Add(int val)
{
	_totalVal += val;
	_availableVal = _totalVal - _usedVal;
}

void Power::Reduce(int val)
{
	_totalVal -= val;
	_availableVal = _totalVal - _usedVal;
}