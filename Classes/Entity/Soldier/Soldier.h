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
	int GetAttack();            //��ȡ��������ֵ
	int GetSpeed();
	void Attack(Entity* target);           //��ͨ���������ȷֱ���ң��ٹ���
	void ForcedAttack(Entity* target);            //ǿ�ƹ�������ν����
	bool init();
	virtual void Die();
	int _numInVec;             //�ڹ�������������
	int _numInTypeVec;         //���Լ�ͬ�൱�е����
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