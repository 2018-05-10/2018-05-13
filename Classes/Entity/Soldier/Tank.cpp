#include "Tank.h"
#include "Resource/Mineral.h"
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

Tank::Tank(int player)
{
	_type=TANK;
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
	_attackInterval = 1.0;
	_player = player;
	_attackDistance = 64;
	_toward = Point(1, 0);
	_target = NULL;
	_soldierID = soldiersID;
	--soldiersID;
} 

Tank::Tank(Mineral* m,int player)
{
	_type=TANK;
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
	_attackInterval = 1.0;
	_attackDistance = 64;
	_player = player;
	_toward = Point(1, 0);
	_target = NULL;
	_soldierID = soldiersID;
	--soldiersID;
}

Tank::~Tank() 
{
}

bool Tank::init()
{
	return true;
}

cocos2d::Animate* Tank::AnimateDie()
{
	int x = _toward.x;
	int y = _toward.y;
	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("TankDie_%d_%d", x, y));
	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Tank::AnimateMove(Point target)
{
	target = MapManager::ChangeToTiledPos(target);
	Point p = MapManager::ChangeToTiledPos(this->getPosition());

	auto dir = target - p;
	int x, y;

	if (dir.x == 1 && dir.y == 0)
	{
		x = 1;y = -1;
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
		x= -1; y = 0;
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

	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("TankMove_%d_%d", x, y));
	Animate* action = Animate::create(animation);


	return action;
}

cocos2d::Animate* Tank::AnimateAttack(Point target)
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

	else if (2.64 < angle&&angle < 3.1415926)

	{

		x = -1; y = 0;

	}

	else if (-0.5 < angle&&angle < 0)

	{

		x = 1; y = 0;

	}

	else if (-1.07 < angle&&angle < -0.5)

	{

		x = 1; y = -1;

	}

	else if (-2.07 < angle&&angle < -1.07)

	{

		x = 0; y = -1;

	}

	else if (-2.64 < angle&&angle < -2.07)
	{
		x = -1; y = -1;
	}
	else
	{
		x = -1; y = 0;
	}

	_toward.x = x;
	_toward.y = y;


	auto animation = AnimationCache::getInstance()->getAnimation(StringUtils::format("TankAttack_%d_%d", x, y));
	Animate* action = Animate::create(animation);

	return action;
}

void Tank::UpdateSprite()
{

	Sprite* spr = Sprite::createWithSpriteFrameName(StringUtils::format("Tank_move_(%d,%d).png",
		static_cast<int>(_toward.x), static_cast<int>(_toward.y)));
	this->BindSprite(spr);
}