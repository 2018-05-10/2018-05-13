#pragma once
#include "Entity/Entity.h"
USING_NS_CC;

class Soldier :public Entity
{
	friend class SoldierManager;
public:
	Soldier();
	virtual ~Soldier();
	int GetAttack();            //获取攻击力数值
	void Attack(Entity* target);           //普通攻击，会先分辨敌我，再攻击
	void ForcedAttack(Entity* target);            //强制攻击，所谓反补
	bool init();
	/*virtual void Die();*/
	int _numInVec;             //在管理类里的总序号
	int _numInTypeVec;         //在自己同类当中的序号
protected:
	int _attack;
	int _speed;
	int _mineralCost;
	float _attackInterval;

	SoldierManager* _pSoldierManager;
};