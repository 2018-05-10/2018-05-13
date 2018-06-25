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
	void Cost(int val);        //���Ŀ��
	void Add(int val);         //���ӿ��


private:
	int _currentVal;       //��ǰ��
};