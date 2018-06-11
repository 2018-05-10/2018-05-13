#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;

class Tank :public Soldier
{
public:
	Tank();
	Tank(Mineral* m, SoldierManager* p);
	~Tank();
	bool init();

	void UpdateSprite();

	cocos2d::Animate* AnimateDie();
	cocos2d::Animate* AnimateMove(Point target);
	cocos2d::Animate* AnimateAttack(Point target);

	CREATE_FUNC(Tank);
private:

};