#pragma once
#include "Entity/Entity.h"
USING_NS_CC;

class Soldier :public Entity
{
	friend class SoldierManager;
public:
	Soldier();
	virtual ~Soldier();
	int GetAttack();            //��ȡ��������ֵ
	void Attack(Entity* target);           //��ͨ���������ȷֱ���ң��ٹ���
	void ForcedAttack(Entity* target);            //ǿ�ƹ�������ν����
	bool init();
	/*virtual void Die();*/
	int _numInVec;             //�ڹ�������������
	int _numInTypeVec;         //���Լ�ͬ�൱�е����
protected:
	int _attack;
	int _speed;
	int _mineralCost;
	float _attackInterval;

	SoldierManager* _pSoldierManager;
};