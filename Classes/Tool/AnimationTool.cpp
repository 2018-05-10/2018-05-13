#include"AnimationTool.h"
#include"Scene\GameScene\GameScene.h"
#include"Entity/Soldier/Soldier.h"
USING_NS_CC;

AnimationTool::AnimationTool()
{
	_animationCache = AnimationCache::getInstance();
}

void AnimationTool::loadAnimation()
{
	for (int x = -1; x < 2; ++x)
	{
		for (int y = -1; y < 2; ++y)
		{
			if (x || y)
			{
				_animationCache->addAnimation(DogMoveAnimation(x, y), StringUtils::format("DogMove_%d_%d", x, y));
				_animationCache->addAnimation(DogAttackAnimation(x, y), StringUtils::format("DogAttack_%d_%d", x, y));
				_animationCache->addAnimation(DogDieAnimation(x, y), StringUtils::format("DogDie_%d_%d", x, y));
				_animationCache->addAnimation(InfantryMoveAnimation(x, y), StringUtils::format("InfantryMove_%d_%d", x, y));
				_animationCache->addAnimation(InfantryAttackAnimation(x, y), StringUtils::format("InfantryAttack_%d_%d", x, y));
				_animationCache->addAnimation(InfantryDieAnimation(x, y), StringUtils::format("InfantryDie_%d_%d", x, y));
				_animationCache->addAnimation(TankMoveAnimation(x, y), StringUtils::format("TankMove_%d_%d", x, y));
				_animationCache->addAnimation(TankAttackAnimation(x, y), StringUtils::format("TankAttack_%d_%d", x, y));
				_animationCache->addAnimation(TankDieAnimation(x, y), StringUtils::format("TankDie_%d_%d", x, y));
			}
		}
	}
}

cocos2d::Animation* AnimationTool::getAnimation(const std::string & animationName)
{
	return _animationCache->getAnimation(animationName);
}


Animation* AnimationTool::DogDieAnimation(int x,int y)
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Dog_move_(%d,%d)_2.png",	x, y));
	frameVec.pushBack(frame);
	frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Dog_die_(%d,%d).png",x, y));
	frameVec.pushBack(frame);

	Animation* animation = Animation::createWithSpriteFrames(frameVec);

	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	return animation;
}

Animation* AnimationTool::DogMoveAnimation(int x, int y)
{
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

	return animation;
}

Animation* AnimationTool::DogAttackAnimation(int x, int y)
{
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

	return animation;
}

Animation* AnimationTool::InfantryAttackAnimation(int x, int y)
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Infantry_attack_(%d,%d).png", x, y));
	frameVec.pushBack(frame);
	frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Infantry_stand_(%d,%d).png", x, y));
	frameVec.pushBack(frame);

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	return animation;
}

Animation* AnimationTool::InfantryMoveAnimation(int x, int y)
{
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

	return animation;
}

Animation* AnimationTool::InfantryDieAnimation(int x, int y)
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 3; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Infantry_die_(%d,%d)_%d.png",x, y, i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	return animation;
}

Animation* AnimationTool::TankDieAnimation(int x, int y)
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 4; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Tank_die_(%d,%d)_%d.png",	x, y, i));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	return animation;
}

Animation* AnimationTool::TankMoveAnimation(int x, int y)
{
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

	return animation;
}

Animation* AnimationTool::TankAttackAnimation(int x, int y)
{
	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame;
	for (int i = 1; i < 3; i++)
	{
		frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Tank_attack_(%d,%d)_%d.png", x, y, i));
		frameVec.pushBack(frame);
	}
	frame = GameScene::_frameCache->getSpriteFrameByName(StringUtils::format("Tank_move_(%d,%d).png", x, y));
	frameVec.pushBack(frame);

	Animation* animation = Animation::createWithSpriteFrames(frameVec);

	animation->setLoops(1);
	animation->setDelayPerUnit(0.2f);

	return animation;
}