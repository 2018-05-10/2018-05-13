#include "Infantry.h"
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

Infantry::Infantry(int player)
{
	_type=INFANTRY;
	_totalHP = 150;
	_currentHP = 150;
	_attack = 50;
	_speed = 1;
	_mineralCost = 20;
	_attackInterval = 1.0;
	_attackDistance = 49;
	_player = player;
	_target = NULL;
	_toward = Point(1, 0);
	_soldierID = soldiersID;
	--soldiersID;
}

Infantry::Infantry(Mineral *m,int player)
{
	_type = INFANTRY;
	_totalHP = 150;
	_currentHP = 150;
	_attack = 50;
	_speed = 1;
	_mineralCost = 20;
	_attackInterval = 0.3;
	_attackDistance = 49;
	_player = player;
	_target = NULL;
	_toward = Point(1, 0);
	_soldierID = soldiersID;
	--soldiersID;

}

Infantry::~Infantry() {}

bool Infantry::init()
{
	return true;
}

cocos2d::Animate* Infantry::AnimateDie()
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 3; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Infantry_die_(%d,%d)_%d.png",
			static_cast<int>(_toward.x), static_cast<int>(_toward.y), i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Infantry::AnimateMove(Point target)
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

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 3; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Infantry_move_(%d,%d)_%d.png", x, y,i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Infantry::AnimateAttack(Point target)
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
	else if (3.64 < angle&&angle < 4.21)
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

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Infantry_attack_(%d,%d).png", x, y));
	frameVec.pushBack(frame);
	frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Infantry_stand_(%d,%d).png", x, y));
	frameVec.pushBack(frame);

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

void Infantry::UpdateSprite()
{
	this->GetSprite()->removeFromParent();
	Sprite* spr = Sprite::createWithSpriteFrameName(StringUtils::format("Infantry_stand_(%d,%d).png",
		static_cast<int>(_toward.x), static_cast<int>(_toward.y)));
	this->BindSprite(spr);
}