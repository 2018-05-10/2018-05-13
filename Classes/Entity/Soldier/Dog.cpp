#include "Dog.h"
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

Dog::Dog(int id)
{
	_type=DOG;
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;
	_attackDistance = 25;
	_player =1;
	_target = NULL;
	_toward = Point(1, 0);
	_ID = id;
	--enemySoldiersID;
}

Dog::Dog(Mineral* m ,int player)
{
	_type = DOG;
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;
	_attackDistance = 25;
	_player = player;
	_target = NULL;
	_toward = Point(1, 0);
	_ID = soldiersID;
	--soldiersID;

}

Dog::~Dog() {}

bool Dog::init()
{
	return true;
}

void Dog::UpdateSprite()
{
	this->GetSprite()->removeFromParent();
	Sprite* spr = Sprite::createWithSpriteFrameName(StringUtils::format("Dog_move_(%d,%d)_1.png", _toward.x, _toward.y));
	this->BindSprite(spr);
}

cocos2d::Animate* Dog::AnimateDie()
{

	int x = _toward.x;
	int y = _toward.y;
	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("DogDie_%d_%d", x, y));
	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Dog::AnimateMove(Point target)
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


	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("DogMove_%d_%d", x, y));
	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Dog::AnimateAttack(Point target)
{
	Point p = this->getPosition();
	target.subtract(p);
	int x = 0; int y = 0;
	float angle = target.getAngle();
	if (0 < angle&&angle < 0.5)
	{
		x = 1; y = 0;
	}
	else if (0.5 < angle&&angle < 1.07)
	{
		x = 1; y = 1;
	}
	else if (1.07 < angle&&angle < 2.07)
	{
		x = 0; y = 1;
	}
	else if (2.07 < angle&&angle < 2.64)
	{
		x = -1; y = 1;
	}
	else if (2.64 < angle&&angle < 3.64)
	{
		x = -1; y = 0;
	}
	else if (3.64 < angle &&angle< 4.21)
	{
		x = -1; y = -1;
	}
	else if (4.12 < angle&&angle < 5.21)
	{
		x = 0; y = -1;
	}
	else if (5.21 < angle&&angle < 5.78)
	{
		x = 1; y = -1;
	}
	else
	{
		x = 1; y = 0;
	}

	_toward.x = x;
	_toward.y = y;


	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("DogAttack_%d_%d", x, y));
	Animate* action = Animate::create(animation);

	return action;
}