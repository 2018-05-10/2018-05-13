#pragma once
#include "Entity/Entity.h"
USING_NS_CC;

class Soldier :public Entity
{
public:
	Soldier();
	~Soldier();
	int GetAttack();
	void Attack(Entity* target);
	bool init();
protected:
	int _attack;
	int _speed;
	int _mineralCost;
};