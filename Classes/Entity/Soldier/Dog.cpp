#include "Dog.h"
#include"Resource/Mineral.h"

using namespace cocos2d;

Dog::Dog()
{
	_whatAmI = "Dog";
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;

	_toward = Point(1, 0);

	Sprite* spr = Sprite::createWithSpriteFrameName("Dog_move_(1,0)_1.png");
	this->BindSprite(spr);
}

Dog::Dog(Mineral* m ,SoldierManager* p)
{
	_whatAmI = "Dog";
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;

	_toward = Point(1, 0);

	Sprite* spr = Sprite::createWithSpriteFrameName("Dog_move_(1,0)_1.png");
	this->BindSprite(spr);

	_pSoldierManager = p;
	m->Cost(_mineralCost);
}

Dog::~Dog() {}

bool Dog::init()
{
	return true;
}

void Dog::UpdateSprite()
{
	this->GetSprite()->removeFromParent();
	Sprite* spr = Sprite::createWithSpriteFrameName(StringUtils::format("Dog_move_(%d,%d)_1.png",_toward.x,_toward.y));
	this->BindSprite(spr);
}

cocos2d::Animate* Dog::AnimateDie(SpriteFrameCache* frameCache)
{
	
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = frameCache->getSpriteFrameByName(StringUtils::format("Dog_move_(%d,%d)_2.png", _toward.x, _toward.y));
	frameVec.pushBack(frame);
	frame = frameCache->getSpriteFrameByName(StringUtils::format("Dog_die_(%d,%d).png", _toward.x, _toward.y));
	frameVec.pushBack(frame);

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Dog::AnimateMove(Point target, SpriteFrameCache* frameCache)
{
	Point p = MapManager::ChangeToTiledPos(this->getPosition());
	target.subtract(p);
	int x = 0; int y = 0;
	float angle = target.getAngle();
	if (0 < angle < 0.5)
	{
		x = 1; y = 0;
	}
	else if (0.5 < angle < 1.07)
	{
		x = 1; y = 1;
	}
	else if (1.07 < angle < 2.07)
	{
		x = 0; y = 1;
	}
	else if (2.07 < angle < 2.64)
	{
		x = -1; y = 1;
	}
	else if (2.64 < angle < 3.64)
	{
		x = -1; y = 0;
	}
	else if (3.64 < angle < 4.21)
	{
		x = -1; y = -1;
	}
	else if (4.12 < angle < 5.21)
	{
		x = 0; y = -1;
	}
	else if (5.21 < angle < 5.78)
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
	for (int i = 1; i < 3; i++)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Dog_move_(%d,%d)_%d.png", x, y, i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Dog::AnimateAttack(Point target, SpriteFrameCache* frameCache)
{
	Point p = this->getPosition();
	target.subtract(p);
	int x = 0; int y = 0;
	float angle = target.getAngle();
	if (0 < angle < 0.5)
	{
		x = 1; y = 0;
	}
	else if (0.5 < angle < 1.07)
	{
		x = 1; y = 1;
	}
	else if (1.07 < angle < 2.07)
	{
		x = 0; y = 1;
	}
	else if (2.07 < angle < 2.64)
	{
		x = -1; y = 1;
	}
	else if (2.64 < angle < 3.64)
	{
		x = -1; y = 0;
	}
	else if (3.64 < angle < 4.21)
	{
		x = -1; y = -1;
	}
	else if (4.12 < angle < 5.21)
	{
		x = 0; y = -1;
	}
	else if (5.21 < angle < 5.78)
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
	for (int i = 2; i > 0; i--)
	{
		frame = frameCache->getSpriteFrameByName(StringUtils::format("Dog_move_(%d,%d)_%d.png", x, y, i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}
