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
	int GetAttack();            //��ȡ��������ֵ
	int GetSpeed();
	void Attack(Entity* target);           //��ͨ���������ȷֱ���ң��ٹ���
	void ForcedAttack(Entity* target);            //ǿ�ƹ�������ν����
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