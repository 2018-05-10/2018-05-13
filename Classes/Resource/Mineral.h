#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Mineral
{
	friend class Dog;
	friend class Infantry;
	friend class Tank;
	friend class Barrack;
	friend class Base;
	friend class Mine;
	friend class PowerStation;
public:
	Mineral();
	~Mineral();
	int GetCurrentVal();
	void Cost(int val);
	void Add(int val);
private:
	int _currentVal;
};