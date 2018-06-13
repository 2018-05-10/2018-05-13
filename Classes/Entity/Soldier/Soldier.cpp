#include "Soldier.h"
#include"Manager/SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Manager/BuildingManager.h"
#include"Manager/MapManager.h"

Soldier::Soldier() {}

Soldier::~Soldier() {}

int Soldier::GetAttack()
{
	return _attack;
}

void Soldier::Attack(Entity* target)     
{
	if (target == nullptr)
	{
		return;
	}
	if (this->GetPlayer() != target->GetPlayer())
	{
		this->GetSprite()->stopAllActions();
		auto func = [&]
		{
			UpdateSprite();
		};
		auto callFunc = CallFunc::create(func);
		auto action = Sequence::create(AnimateAttack(this->getPosition()), callFunc,NULL);
		this->GetSprite()->runAction(AnimateAttack(this->getPosition()));

		target->Hit(_attack);
	}
}

void Soldier::ForcedAttack(Entity* target)       //强制攻击，所谓反补，建议组合按键：A+鼠标右键
{
	if (target == NULL)
	{
		return;
	}
	target->Hit(_attack);
}

bool Soldier::init()
{
	return true;
}

void Soldier::Die()     
{
	_pSoldierManager->DestroySoldier(this);
}

int Soldier::GetMineralCost()const
{
	return _mineralCost;
}

int Soldier::GetSpeed()
{
	return _speed;
}

void Soldier::SearchEnemyUpdate(float dt)
{

	int leastDir =1000000;
	Entity* target=nullptr;
	for (auto building : static_cast<GameScene*>(this->getParent()->getParent())->GetBuildingManager()->_enemyBuildingVec)
	{

		if (building != nullptr)
		{
			auto targetPos = static_cast<GameScene*>(this->getParent()->getParent())->GetMapManager()->ChangeToTiledPos(building->getPosition()); 
			auto soldierPos= static_cast<GameScene*>(this->getParent()->getParent())->GetMapManager()->ChangeToTiledPos(this->getPosition());
			Point deltaPos = targetPos - soldierPos;
			if (pow(deltaPos.x, 2) + pow(deltaPos.y, 2) <leastDir)
			{
				target = building;
				leastDir = pow(deltaPos.x, 2) + pow(deltaPos.y, 2);
			}
			
		}
	}
	if (leastDir <= _attackDistance)
	{
		this->Attack(target);
	}
}
float Soldier::GetAttackInterval()
{
	return _attackInterval;
}
cocos2d::Animate* Soldier::AnimateMove(Point target)
{
	return nullptr;
}
cocos2d::Animate* Soldier::AnimateDie()
{
	return nullptr;
}
cocos2d::Animate* Soldier::AnimateAttack(Point target)
{
	return nullptr;
}

void Soldier::UpdateSprite()
{

}