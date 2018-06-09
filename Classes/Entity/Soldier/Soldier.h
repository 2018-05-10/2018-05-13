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
	int GetAttack();            //获取攻击力数值
	int GetSpeed();
	void Attack(Entity* target);           //普通攻击，会先分辨敌我，再攻击
	void ForcedAttack(Entity* target);            //强制攻击，所谓反补
	bool init();
	virtual void Die();
	int _numInVec;             //在管理类里的总序号
	int _numInTypeVec;         //在自己同类当中的序号
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