#pragma once
#include"cocos2d.h"
#include"Soldier.h"
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
	virtual cocos2d::Animate* AnimateMove(cocos2d::Point target);
	virtual cocos2d::Animate* AnimateAttack(cocos2d::Point target);

private:

};