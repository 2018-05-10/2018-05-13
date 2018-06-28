#include "Explosion.h"

#include"Resource/Mineral.h"

#include"Scene/GameScene/GameScene.h"

#include"Manager/MapManager.h"



#define BASE 1

#define FACTORY 2

#define BARRACK 3

#define MINE 4

#define POWERSTATION 5

#define INFANTRY 6

#define DOG 7

#define TANK 8

#define EXPLOSION 9



Explosion::Explosion(int id)

{

	_type = EXPLOSION;

	_totalHP = 50;

	_currentHP = 50;

	_attack = 100;

	_speed = 6;

	_mineralCost = 70;

	_attackInterval = 0.0;

	_attackDistance = 25;

	_player = 1;

	_target = NULL;

	_toward = Point(1, 0);

	_ID = id;

	--enemySoldiersID;

}



Explosion::Explosion(Mineral* m, int player)

{

	_type = EXPLOSION;

	_totalHP = 50;

	_currentHP = 50;

	_attack = 100;

	_speed = 6;

	_mineralCost = 70;

	_attackInterval = 0.0;

	_attackDistance = 25;

	_player = player;

	_target = NULL;

	_toward = Point(1, 0);

	_ID = soldiersID;

	--soldiersID;

}



Explosion::~Explosion()

{

}



bool Explosion::init()

{

	return true;

}



void Explosion::UpdateSprite()

{

	this->GetSprite()->removeFromParent();

	Sprite* spr = Sprite::createWithSpriteFrameName(StringUtils::format("Explosion_move_(%d,%d).png", _toward.x, _toward.y));

	this->BindSprite(spr);

}



cocos2d::Animate* Explosion::AnimateDie()

{

	int x = _toward.x;
	int y = _toward.y;

	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("ExplosionDie_%d_%d", x, y));
	Animate* action = Animate::create(animation);

	return action;

}



cocos2d::Animate* Explosion::AnimateMove(Point target)

{

	target = MapManager::ChangeToTiledPos(target);
	Point p = MapManager::ChangeToTiledPos(this->getPosition());



	auto dir = target - p;
	int x, y;

	if (dir.x == 1 && dir.y == 0)
	{
		x = 1; y = -1;
	}

	else if (dir.x == 1 && dir.y == 1)
	{
		x = 0; y = -1;
	}

	else if (dir.x == 0 && dir.y == 1)
	{
		x = -1; y = -1;
	}

	else if (dir.x == -1 && dir.y == 1)
	{
		x = -1; y = 0;
	}

	else if (dir.x == -1 && dir.y == 0)
	{
		x = -1; y = 1;
	}

	else if (dir.x == -1 && dir.y == -1)

	{
		x = 0; y = 1;
	}

	else if (dir.x == 0 && dir.y == -1)

	{
		x = 1; y = 1;
	}

	else if (dir.x == 1 && dir.y == -1)

	{
		x = 1; y = 0;
	}
	else
	{
		x = 1; y = 1;
	}


	_toward.x = x;
	_toward.y = y;

	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("ExplosionMove_%d_%d", x, y));
	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Explosion::AnimateAttack(Point target)
{
	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("ExplosionAttack_%d_%d", _toward.x, _toward.y));
	Animate* action = Animate::create(animation);

	return action;
}