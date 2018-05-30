#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Power 
{
	friend class Barrack;
	friend class Base;
	friend class Mine;
	friend class PowerStation;
public:
	Power();
	~Power();
	int GetTotalVal();
	int GetUsedVal();
	int GetAvailableVal();
	void Use(int val);
	void Add(int val);
	void Reduce(int val);
private:
	int _totalVal;
	int _usedVal;
	int _availableVal;

};