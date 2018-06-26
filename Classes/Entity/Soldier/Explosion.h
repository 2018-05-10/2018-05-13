#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;

class Explosion :public Soldier
{
public:
	Explosion(int player);
	Explosion(Mineral* m, int player);
	~Explosion();
	bool init();

	void UpdateSprite();

	virtual cocos2d::Animate* AnimateDie();
	virtual cocos2d::Animate* AnimateMove(Point target);
	virtual cocos2d::Animate* AnimateAttack(Point target);


private:
};