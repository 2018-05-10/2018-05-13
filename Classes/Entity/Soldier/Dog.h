#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;

class Dog :public Soldier
{
public:
	Dog(int player);
	Dog(Mineral* m,int player);
	~Dog();
	bool init();

	void UpdateSprite();

	virtual cocos2d::Animate* AnimateDie();
	virtual cocos2d::Animate* AnimateMove(Point target);
	virtual cocos2d::Animate* AnimateAttack(Point target);


private:
};