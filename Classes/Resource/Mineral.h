#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Mineral :public Node
{
	friend class BuildingManager;
public:
	Mineral();
	~Mineral();
	CREATE_FUNC(Mineral);
	bool init();
	int GetCurrentVal();
	void Cost(int val);        //消耗矿产
	void Add(int val);         //增加矿产


private:
	int _currentVal;       //当前量
};