#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;
class SoldierManager;

class Infantry :public Soldier
{
public:
	Infantry();
	Infantry(Mineral *m, SoldierManager* p,int player);
	~Infantry();
	bool init();

	void UpdateSprite();

	cocos2d::Animate* AnimateDie();
	cocos2d::Animate* AnimateMove(Point target);
	cocos2d::Animate* AnimateAttack(Point target);

	CREATE_FUNC(Infantry);
private:

};