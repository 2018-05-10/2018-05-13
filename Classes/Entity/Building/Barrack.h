#pragma once
#include "Building.h"
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Barrack :public Building
{
	friend class MenuLayer;
public:
	Barrack();
	Barrack(Power* p, Mineral* m,int player);       //��������������ֱ���Ϊ���޸���Ӧ�ĵ�����������Լ�ȷ���ö������ĸ�������Ĺ���֮��
	~Barrack();
	bool init();
	int GetPowerCost();     //�����ĵĵ���
	int GetMineralCost();       //�����ĵĿ���

	void BarrackUpdate(float dt);

	CREATE_FUNC(Barrack);
private:
	std::queue<char*> _buildingList;
};