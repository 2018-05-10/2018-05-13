#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Mineral;

class Tank :public Soldier
{
public:
	Tank(int player);
	Tank(Mineral* m,int player);
	~Tank();
	bool init();

	void UpdateSprite();

	virtual cocos2d::Animate* AnimateDie();
	virtual cocos2d::Animate* AnimateMove(Point target);
	virtual cocos2d::Animate* AnimateAttack(Point target);


private:

};