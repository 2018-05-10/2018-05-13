#include "Building.h"
#include"Manager/BuildingManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Manager\SoldierManager.h"
#include"Manager/MapManager.h"
#include"PowerStation.h"
#include"SimpleAudioEngine.h"
#include"Entity/Player.h"

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8
#define EXPLOSION 9
#define CREATE_ENEMY 1000
#define SET_ENEMY_TARGET 1001
#define SET_ENEMY_TARGET_ENEMY 1002
#define ENEMY_DIE 1003

Building::Building() 
{

}

Building::~Building() {}

bool Building::IsWorking()
{
	return _isWorking;
}

void Building::SetIsWorking(bool a)
{
	_isWorking = a;
}



bool Building::init()
{
	return true;
}

void Building::Die()
{
	
	if (_isDead)
	{
		return;
	}
	for (int i = 0; i < 5; ++i)
	{
		Player::getInstance()->client->SendData(0, 0, 0, this->GetID(), this->GetType(), ENEMY_DIE);

	}
	_isDead = true;
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/BoomSound.wav");
	MapManager::RemoveBuilding(this, _type);
	
	BuildingManager::DestroyBuilding(this);
}



//========building ID by cyy=====
int Building::buildingsID;
int Building::enemyBuildingsID;



void Building::BuildingUpdate(float dt)
{
	if (_timeBar && !_player)
	{
		this->unscheduleUpdate();
		_timeBar->removeFromParent();

	}	if (_player)
	{
		GetSprite()->setColor(Color3B(255, 255, 255));
		return;
	}
	if (_pPower->GetUsedVal() > _pPower->GetTotalVal())
	{
		_isWorking = false;
		this->GetSprite()->setColor(Color3B(100, 100, 100));
	}
	else
	{
		GetSprite()->setColor(Color3B(255, 255, 255));
		_isWorking = true;

		int freePower = _pPower->GetAvailableVal();
		if (_type == MINE && !_player)
		{
			BuildingManager::UpdateMineralPerSecond();
		}
		if (_type == POWERSTATION)
		{
			if (freePower > 0&&!_player)
			{
				_pPower->Add(static_cast<PowerStation*>(this)->GetPowerProduce());

				for (auto building:BuildingManager::_buildingMap)
				{
					if ((!building.second->_isWorking) && (building.second->_powerCost <= freePower))
					{
						freePower -= building.second->_powerCost;
						building.second->_isWorking = true;
						_pPower->Use(building.second->_powerCost);
					}
				}
			}
		}
		
	}
	
}

void Building::update(float dt)
{ 
	if (_timeBar)
	{
		
		_timeBar->setScaleX(_timeBar->getScaleX() + 0.016/static_cast<float>(_timeToBuild));
	}
}