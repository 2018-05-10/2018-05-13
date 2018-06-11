#pragma once
#include "Building.h"
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Barrack :public Building
{
public:
	Barrack();
	Barrack(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);       //��������������ֱ���Ϊ���޸���Ӧ�ĵ�����������Լ�ȷ���ö������ĸ�������Ĺ���֮��
	~Barrack();
	bool init();
	int GetPowerCost();     //�����ĵĵ���
	int GetMineralCost();       //�����ĵĿ���
	

	CREATE_FUNC(Barrack);
private:
};