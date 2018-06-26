#pragma once
#include "cocos2d.h"

class Soldier;
class AnimationTool
{
public:

	static AnimationTool* getInstance()
	{
		static AnimationTool INSTANCE;
		return &INSTANCE;
	}

	cocos2d::Animation * getAnimation(const std::string & animationName);

	void loadAnimation();

	cocos2d::Animation* DogDieAnimation(int x,int y);
	cocos2d::Animation* DogMoveAnimation(int x, int y);
	cocos2d::Animation* DogAttackAnimation(int x, int y);

	cocos2d::Animation* InfantryDieAnimation(int x, int y);
	cocos2d::Animation* InfantryMoveAnimation(int x, int y);
	cocos2d::Animation* InfantryAttackAnimation(int x, int y);

	cocos2d::Animation* TankDieAnimation(int x, int y);
	cocos2d::Animation* TankMoveAnimation(int x, int y);
	cocos2d::Animation* TankAttackAnimation(int x, int y);

	cocos2d::Animation* ExplosionDieAnimation(int x,int y);
	cocos2d::Animation* ExplosionMoveAnimation(int x, int y);
	cocos2d::Animation* ExplosionAttackAnimation(int x, int y);
	
private:
	AnimationTool();
;	cocos2d::AnimationCache * _animationCache;
	unsigned int getFlag(const std::string & animationName);
};
