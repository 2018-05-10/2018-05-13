#include "Tank.h"
#include "Resource/Mineral.h"

using namespace cocos2d;

Tank::Tank()
{
	_whatAmI = "Tank";
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
	_attackInterval = 1.0;

	_toward = Point(1, 0);

	Sprite* spr = Sprite::create("Tank.png");
	spr->setScale(2.0);
	this->BindSprite(spr);
} 

Tank::Tank(Mineral* m, SoldierManager* p)
{
	_whatAmI = "Tank";
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
	_attackInterval = 1.0;

	_toward = Point(1, 0);

	_pSoldierManager = p;
	m->Cost(_mineralCost);
}

Tank::~Tank() 
{
}

bool Tank::init()
{
	return true;
}

void Tank::UpdateSprite()
{
	Sprite* temp = Sprite::create(StringUtils::format("Tank_move_(%d,%d)", _toward.x, _toward.y));
	Sprite* spr = this->GetSprite();
	spr->setTexture(temp->getTexture());
	spr->setTextureRect(temp->getTextureRect());
}

cocos2d::Animate* Tank::AnimateDie()
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 4; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("Tank_die_(%d,%d)_%d.png", _toward.x, _toward.y, i), Rect(0, 0, 97, 97));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Tank::AnimateMove(Point target)
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
	for (int i = 1; i < 3; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("Tank_move_(%d,%d).png", x, y, i), Rect(0, 0, 97, 97));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

cocos2d::Animate* Tank::AnimateAttack(Point target)
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
	for (int i = 1; i < 3; i++)
	{
		frame = SpriteFrame::create(StringUtils::format("Tank_attack_(%d,%d)_%d.png", x, y, i), Rect(0, 0, 97, 97));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}