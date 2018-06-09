#pragma once
#include "Entity/Entity.h"
#include<deque>
USING_NS_CC;

class Soldier :public Entity
{
	friend class SoldierManager;
public:
	Soldier();
	virtual ~Soldier();
	int GetAttack();            //��ȡ��������ֵ
	int GetSpeed();
	void Attack(Entity* target);           //��ͨ���������ȷֱ���ң��ٹ���
	void ForcedAttack(Entity* target);            //ǿ�ƹ�������ν����
	bool init();
	virtual void Die();
	int _numInVec;             //�ڹ�������������
	int _numInTypeVec;         //���Լ�ͬ�൱�е����
	int GetMineralCost()const;

	void SearchEnemyUpdate(float dt);

	Point _targetPoint=Point(-1,-1);
	std::deque<Point> _path;

protected:
	int _attack;
	int _speed;
	int _mineralCost;
	float _attackInterval;

	SoldierManager* _pSoldierManager;
};