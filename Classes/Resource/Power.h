#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Power :public Node
{
public:
	Power();
	~Power();
	CREATE_FUNC(Power);
	bool init();

	int GetTotalVal();
	int GetUsedVal();
	int GetAvailableVal();
	void Use(int val);          //向杯子里面倒水
	void Free(int val);          //将杯子里的水倒出来
	void Add(int val);           //增加总容量
	void Reduce(int val);        //减少总容量
private:
	int _totalVal;
	int _usedVal;
	int _availableVal;
};