#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;

class Dog :public Soldier
{
public:
	Dog();
	Dog(Mineral* m, SoldierManager* p);
	~Dog();
	bool init();

	void UpdateSprite();

	cocos2d::Animate* AnimateDie();
	cocos2d::Animate* AnimateMove(Point target);
	cocos2d::Animate* AnimateAttack(Point target);

	CREATE_FUNC(Dog);
private:
};