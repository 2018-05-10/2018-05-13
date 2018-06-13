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

	cocos2d::Animate* AnimateDie(SpriteFrameCache* frameCache);
	cocos2d::Animate* AnimateMove(Point target, SpriteFrameCache* frameCache);
	cocos2d::Animate* AnimateAttack(Point target, SpriteFrameCache* frameCache);

	CREATE_FUNC(Dog);
private:
};