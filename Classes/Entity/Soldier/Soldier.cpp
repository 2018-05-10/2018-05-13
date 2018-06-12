#include "Soldier.h"
#include"Manager/SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Manager/BuildingManager.h"

Soldier::Soldier() {}

Soldier::~Soldier() {}

int Soldier::GetAttack()
{
	return _attack;
}

void Soldier::Attack(Entity* target)     
{
	if (target == NULL)
	{
		return;
	}
	if (this->GetPlayer() != target->GetPlayer())
	{
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
	for (auto building : static_cast<GameScene*>(this->getParent()->getParent())->GetBuildingManager()->_enemyBuildingVec)
	{

		if (building != nullptr)
		{


			auto deltaPos = building->getPosition() - this->getPosition();
			this->Attack(building);
		}
	}
}