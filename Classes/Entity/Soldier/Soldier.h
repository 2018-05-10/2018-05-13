<<<<<<< HEAD
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
=======
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
>>>>>>> 56e4016d2c955433aa3b7ab48b66f586a308c550
};