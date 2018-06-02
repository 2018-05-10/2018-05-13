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
	void Use(int val);          //�������浹ˮ
	void Free(int val);          //���������ˮ������
	void Add(int val);           //����������
	void Reduce(int val);        //����������
private:
	int _totalVal;
	int _usedVal;
	int _availableVal;
};