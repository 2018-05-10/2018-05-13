#include "Dog.h"
#include"Resource/Mineral.h"
#include"Scene/GameScene/GameScene.h"

Dog::Dog(int player)
{
	_whatAmI = "Dog";
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;
	_attackDistance = 25;
	_player = player;

}

Dog::Dog(Mineral* m ,int player)
{
	_whatAmI = "Dog";
	_totalHP = 100;
	_currentHP = 100;
	_attack = 20;
	_speed = 6;
	_mineralCost = 10;
	_attackInterval = 0.8;
	_attackDistance = 25;
	_player = player;
	_target = NULL;

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
	Sprite* spr = Sprite::createWithSpriteFrameName(StringUtils::format("Dog_move_(%d,%d)_1.png", _toward.x, _toward.y));
	this->BindSprite(spr);
}

cocos2d::Animate* Dog::AnimateDie()
{

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Dog_move_(%d,%d)_2.png", _toward.x, _toward.y));
	frameVec.pushBack(frame);
	frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Dog_die_(%d,%d).png", _toward.x, _toward.y));
	frameVec.pushBack(frame);

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Dog::AnimateMove(Point target)
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


	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 3; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Dog_move_(%d,%d)_%d.png", x, y, i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);

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


	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 2; i > 0; i--)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Dog_move_(%d,%d)_%d.png", x, y, i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}