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

		auto func = [=]()
		{
			GameScene::GetSoldierManager()->Move(this);
		};
		auto callFunc = CallFunc::create(func);
	
		this->GetSprite()->runAction(AnimateAttack(target->getPosition()));

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
	MapManager::RemoveSoldier(this);
	if (_player)
	{
		for (auto soldier : SoldierManager::_soldierVec)
		{
			if (soldier->_target == this)
			{
				soldier->_target = nullptr;
			}
		}
	}
	auto func = [&, this]()
	{
		GameScene::GetSoldierManager()->DestroySoldier(this);
	};
	auto callFunc = CallFunc::create(func);
	this->GetSprite()->runAction(Sequence::create(AnimateDie(),callFunc, NULL));
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

	if (this->_target)
	{
		auto targetPos = MapManager::ChangeToTiledPos(_target->getPosition());
		auto soldierPos = MapManager::ChangeToTiledPos(this->getPosition());
		Point deltaPos = targetPos - soldierPos;
		if (pow(deltaPos.x, 2) + pow(deltaPos.y, 2) < this->_attackDistance)
		{
			this->Attack(this->_target);
			return;
		}
	}
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
	if (leastDir <= _attackDistance)
	{
		this->Attack(target);
		return;
	}
	leastDir = 1000000;
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

Entity* Soldier::GetTarget()
{
	return _target;
}

void Soldier::UpdateSprite()
{

}