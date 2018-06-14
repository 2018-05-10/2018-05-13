#include "Soldier.h"
#include"Manager/SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Manager/BuildingManager.h"
#include"Manager/SoldierManager.h"
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
	GameScene::GetSoldierManager()->DestroySoldier(this);
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
	for (auto soldier : SoldierManager::_enemySoldier)
	{
		if (soldier != nullptr)
		{
			auto targetPos = MapManager::ChangeToTiledPos(soldier->getPosition());
			auto soldierPos = MapManager::ChangeToTiledPos(this->getPosition());
			Point deltaPos = targetPos - soldierPos;
			if (pow(deltaPos.x, 2) + pow(deltaPos.y, 2) <leastDir)
			{
				target =soldier;
				leastDir = pow(deltaPos.x, 2) + pow(deltaPos.y, 2);
			}
		}
	}
	for (auto building :BuildingManager::_enemyBuildingVec)
	{

		if (building != nullptr)
		{
			auto targetPos = MapManager::ChangeToTiledPos(building->getPosition()); 
			auto soldierPos= MapManager::ChangeToTiledPos(this->getPosition());
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