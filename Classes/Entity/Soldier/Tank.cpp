#include "Tank.h"
#include "Resource/Mineral.h"
#include"Scene/GameScene/GameScene.h"
#include"Manager/MapManager.h"
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

} 

Tank::Tank(Mineral* m, SoldierManager* p,int player)
{
	_whatAmI = "Tank";
	_totalHP = 300;
	_currentHP = 300;
	_attack = 150;
	_speed = 3;
	_mineralCost = 50;
	_attackInterval = 1.0;
	_attackDistance = 64;
	_player = player;
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

cocos2d::Animate* Tank::AnimateDie()
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 4; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Tank_die_(%d,%d)_%d.png",
			static_cast<int>(_toward.x), static_cast<int>(_toward.y), i));
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

	target = static_cast<GameScene*>(this->getParent()->getParent())->GetMapManager()->ChangeToTiledPos(target);
	Point p = static_cast<GameScene*>(this->getParent()->getParent())->GetMapManager()->ChangeToTiledPos(this->getPosition());
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
	for (int i = 1; i < 2; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Tank_move_(%d,%d).png", x, y));
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
	target = static_cast<GameScene*>(this->getParent()->getParent())->GetMapManager()->ChangeToTiledPos(target);
	Point p = static_cast<GameScene*>(this->getParent()->getParent())->GetMapManager()->ChangeToTiledPos(this->getPosition());
	target.subtract(p);
	int x = 0; int y = 0;
	float angle = target.getAngle();
	if (0 < angle < 0.5)
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
	for (int i = 1; i < 3; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Tank_attack_(%d,%d)_%d.png", x, y, i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	Animate* action = Animate::create(animation);

	return action;
}

void Tank::UpdateSprite()
{
	this->GetSprite()->removeFromParent();
	Sprite* spr = Sprite::createWithSpriteFrameName(StringUtils::format("Tank_move_(%d,%d)",
		static_cast<int>(_toward.x), static_cast<int>(_toward.y)));
	this->BindSprite(spr);
}