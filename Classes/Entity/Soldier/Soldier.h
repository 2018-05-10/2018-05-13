#pragma once
#include "Entity/Entity.h"
#include<deque>
USING_NS_CC;

class Soldier :public Entity
{
	friend class SoldierManager;
	friend class GameScene;
	friend class NetScene;
public:
	Soldier();
	virtual ~Soldier();
	float GetAttackInterval();
	int GetAttack();            //获取攻击力数值
	int GetSpeed();
	void Attack(Entity* target);           //普通攻击，会先分辨敌我，再攻击
	void ForcedAttack(Entity* target);            //强制攻击，所谓反补
	void Aoe(cocos2d::Point,int dir);
	bool init();
	virtual void Die();
	int GetMineralCost()const;
	virtual void UpdateSprite();

	virtual cocos2d::Animate* AnimateDie();
	virtual cocos2d::Animate* AnimateMove(Point target);
	virtual cocos2d::Animate* AnimateAttack(Point target);

	void SearchEnemyUpdate(float dt);
	void EnemySearchEnemyUpdate(float dt);





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
	static int soldiersID;
	static int enemySoldiersID;


	SoldierManager* _pSoldierManager;
};