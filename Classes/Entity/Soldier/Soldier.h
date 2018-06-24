#pragma once
#include "Entity/Entity.h"
#include<deque>
USING_NS_CC;

class Soldier :public Entity
{
	friend class SoldierManager;
	friend class GameScene;
public:
	Soldier();
	virtual ~Soldier();
	float GetAttackInterval();
	int GetAttack();            //获取攻击力数值
	int GetSpeed();
	void Attack(Entity* target);           //普通攻击，会先分辨敌我，再攻击
	void ForcedAttack(Entity* target);            //强制攻击，所谓反补
	bool init();
	virtual void Die();
	int _numInVec;             //在管理类里的总序号
	int _numInTypeVec;         //在自己同类当中的序号
	int GetMineralCost()const;
	virtual void UpdateSprite();

	virtual cocos2d::Animate* AnimateDie();
	virtual cocos2d::Animate* AnimateMove(Point target);
	virtual cocos2d::Animate* AnimateAttack(Point target);

	void SearchEnemyUpdate(float dt);
	void EnemySearchEnemyUpdate(float dt);

	int GetSoldierID();
	static int soldiersID;
	int _soldierID;


	Point _targetPoint=Point(-1,-1);
	std::deque<Point> _path;

	Entity* GetTarget();
	Entity *_target;

protected:
	int _attack;
	int _speed;
	int _mineralCost;
	float _attackInterval;
	int _attackDistance;
	Point _toward;


	SoldierManager* _pSoldierManager;
};