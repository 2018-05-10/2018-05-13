#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;
class SoldierManager;

class Infantry :public Soldier
{
public:
	Infantry(int player);
	Infantry(Mineral *m, int player);
	~Infantry();
	bool init();

	void UpdateSprite();

	cocos2d::Animate* AnimateDie();
	cocos2d::Animate* AnimateMove(Point target);
	cocos2d::Animate* AnimateAttack(Point target);

private:

};