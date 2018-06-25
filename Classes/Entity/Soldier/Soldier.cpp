#include "Soldier.h"
#include"Manager/SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Manager/BuildingManager.h"
#include"Manager/SoldierManager.h"
#include"Manager/MapManager.h"
#include"SimpleAudioEngine.h"

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8

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
	if (this->GetPlayer() != target->GetPlayer()&&!this->_isDead)
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
	_isDead = true;
	if (_type=TANK)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/BoomSound.wav");
	}
	MapManager::RemoveSoldier(this);
	
	auto func = [this]()
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

	
	if (this->_target&&!_target->Isdead())
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
	for (auto soldier : SoldierManager::_enemySoldierMap)
	{

			auto targetPos = MapManager::ChangeToTiledPos(soldier.second->getPosition());
			auto soldierPos = MapManager::ChangeToTiledPos(this->getPosition());
			Point deltaPos = targetPos - soldierPos;
			if (pow(deltaPos.x, 2) + pow(deltaPos.y, 2) <leastDir)
			{
				target =soldier.second;
				leastDir = pow(deltaPos.x, 2) + pow(deltaPos.y, 2);
			}
		
	}
	if (leastDir <= _attackDistance)
	{
		this->Attack(target);
		return;
	}
	leastDir = 1000000;
	for (auto building :BuildingManager::_enemyBuildingMap)
	{


			auto targetPos = MapManager::ChangeToTiledPos(building.second->getPosition()); 
			auto soldierPos= MapManager::ChangeToTiledPos(this->getPosition());
			Point deltaPos = targetPos - soldierPos;
			if (pow(deltaPos.x, 2) + pow(deltaPos.y, 2) <leastDir)
			{
				target = building.second;
				leastDir = pow(deltaPos.x, 2) + pow(deltaPos.y, 2);
			}
			
	}
	if (leastDir <= _attackDistance)
	{
		this->Attack(target);
	}
}
void Soldier::EnemySearchEnemyUpdate(float dt)
{

	int leastDir = 1000000;
	Entity* target = nullptr;


	if (this->_target && !_target->Isdead())
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
	for (auto soldier : SoldierManager::_soldierMap)
	{

			auto targetPos = MapManager::ChangeToTiledPos(soldier.second->getPosition());
			auto soldierPos = MapManager::ChangeToTiledPos(this->getPosition());
			Point deltaPos = targetPos - soldierPos;
			if (pow(deltaPos.x, 2) + pow(deltaPos.y, 2) <leastDir)
			{
				target = soldier.second;
				leastDir = pow(deltaPos.x, 2) + pow(deltaPos.y, 2);
			}
		
	}
	if (leastDir <= _attackDistance)
	{
		this->Attack(target);
		return;
	}
	leastDir = 1000000;
	for (auto building : BuildingManager::_buildingMap)
	{


			auto targetPos = MapManager::ChangeToTiledPos(building.second->getPosition());
			auto soldierPos = MapManager::ChangeToTiledPos(this->getPosition());
			Point deltaPos = targetPos - soldierPos;
			if (pow(deltaPos.x, 2) + pow(deltaPos.y, 2) <leastDir)
			{
				target = building.second;
				leastDir = pow(deltaPos.x, 2) + pow(deltaPos.y, 2);
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

int Soldier::GetSoldierID()
{
	return _soldierID;
}

int Soldier::soldiersID = -2;