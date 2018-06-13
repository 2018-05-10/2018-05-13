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

	cocos2d::Animate* AnimateDie(SpriteFrameCache* frameCache);
	cocos2d::Animate* AnimateMove(Point target, SpriteFrameCache* frameCache);
	cocos2d::Animate* AnimateAttack(Point target, SpriteFrameCache* frameCache);

	CREATE_FUNC(Tank);
private:

};