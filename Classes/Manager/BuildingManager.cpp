#include"BuildingManager.h"
#include"Entity/Building/Base.h"
#include"Entity/Building/Barrack.h"
#include"Entity/Building/Factory.h"
#include"Entity/Building/Mine.h"
#include"Entity/Building/PowerStation.h"
#include"Scene/GameScene/GameScene.h"
#include"Scene/GameScene/MenuLayer.h"
#include"Manager\SoldierManager.h"
USING_NS_CC;

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8

Building* BuildingManager::CreateBuilding(int BuildingTypeName)
{
	Building* B = NULL;
	Sprite* spr = NULL;
	if (BuildingTypeName == BASE)
	{
		B = new Base(_pPower, _pMineral, 0);
		spr = Sprite::createWithSpriteFrameName("Base.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == BARRACK)
	{
		B = new Barrack(_pPower, _pMineral, 0);
		spr = Sprite::createWithSpriteFrameName("Barrack.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
		B->schedule(schedule_selector(Barrack::BarrackUpdate), 0.5);
	}
	else if (BuildingTypeName == MINE)
	{
		B = new Mine(_pPower, _pMineral, 0);
		spr = Sprite::createWithSpriteFrameName("Mine.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == POWERSTATION)
	{
		B = new PowerStation(_pPower, _pMineral, 0);
		spr = Sprite::createWithSpriteFrameName("PowerStation.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == FACTORY)
	{
		B = new Factory(_pPower, _pMineral, 0);
		spr = Sprite::createWithSpriteFrameName("Factory.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
		B->schedule(schedule_selector(Factory::FactoryUpdate), 10);
	}
	else
	{
		return NULL;
	}

		B->autorelease();
		B->_hpBar = Sprite::createWithSpriteFrameName("GreenBar.png");
		B->addChild(B->_hpBar);
		B->_hpBar->setContentSize(Size(200, 5));
		B->_hpBar->setPosition(130, 220);
		B->_hpBar->setGlobalZOrder(9);
		B->_timeBar = Sprite::createWithSpriteFrameName("BlueBar.png");
		B->addChild(B->_timeBar);
		B->_timeBar->setContentSize(Size(200, 5));
		B->_timeBar->setPosition(130, 240);
		B->_timeBar->setScaleX(0);
		B->_timeBar->setGlobalZOrder(9);
		B->scheduleUpdate();
		B->scheduleOnce(schedule_selector(Building::BuildingUpdate), B->_timeToBuild);
		_buildingMap.insert(std::make_pair(B->GetID(), B));


		return B;
}

void BuildingManager::BindPower(Power* p)
{
	_pPower = p;
}

void BuildingManager::BindMineral(Mineral* m)
{
	_pMineral = m;

}

void BuildingManager::UpdateMineralPerSecond()
{
	int val=0;

	for (auto building:_buildingMap)
	{
		if ((building.second->_type==MINE) && (building.second->_isWorking))
		{
			val += building.second->_mineralProducePerSecond;
		}
	}
	_mineralPerSecond = val;
}



TMXTiledMap* BuildingManager::GetMap()
{
	return 	GameScene::GetMap();
}
SoldierManager*  BuildingManager::GetSoldierManager()
{
	return  	GameScene::GetSoldierManager();
}
MapManager* BuildingManager::GetMapManager()
{
	return 	GameScene::GetMapManager();
}
Mineral* BuildingManager::GetMineral()
{
	return  	GameScene::GetMineral();
}
Power* BuildingManager::GetPower()
{
	return  	GameScene::GetPower();
}
MenuLayer* BuildingManager::GetMenuLayer()
{
	return 	GameScene::GetMenuLayer();
}

int BuildingManager::GetMineralPerSecond()const
{
	return _mineralPerSecond;
}

bool BuildingManager::BuildingResourceCheck(int name)
{
	int mineralCost, powerCost;
	switch (name)
	{
	case(BASE):
		mineralCost =0 ;
		powerCost =40 ;
		break;
	case(FACTORY):
		mineralCost = 100;
		powerCost =35 ;
		break;
	case(BARRACK):
		mineralCost =100 ;
		powerCost = 35;
		break;
	case(MINE):
		mineralCost = 50;
		powerCost =25 ;
		break;
	case(POWERSTATION):
		mineralCost = 100;
		powerCost = 0;
		break;
	}
	if (GetMineral()->GetCurrentVal() - mineralCost < 0)
	{
		return false;
	}
	if (GetPower()->GetAvailableVal() - powerCost < 0)
	{
		return false;
	}
	return true;
}

void BuildingManager::DestroyBuilding(Building* B)
{
	if (B->_player)
	{
		_enemyBuildingMap.erase(B->GetID());
	}
	else
	{
		_buildingMap.erase(B->GetID());
	}
	if (B->_type==POWERSTATION&&!B->_player&&B->IsWorking())
	{
	for(auto building:_buildingMap)
	{
			if (GameScene::GetPower()->GetAvailableVal()<0)
			{	
					building.second->_isWorking = false;
					GameScene::GetPower()->_availableVal += building.second->_powerCost;
					building.second->GetSprite()->setColor(Color3B(100, 100, 100));
					++GameScene::GetPower()->_availableVal;
			}
			else
			{
				break;
			}
		}
	}
	if (B->_type == MINE && !B->_player&&B->_isWorking)
	{
		UpdateMineralPerSecond();
	}
	
	if (B->_player)
	{
		for (auto soldier : SoldierManager::_soldierMap)
		{
			if (soldier.second->_target == B)
			{
				soldier.second->_target = nullptr;
			}
		}
	}
	else
	{
		for (auto soldier : SoldierManager::_enemySoldierMap)
		{
			if (soldier.second->_target == B)
			{
				soldier.second->_target = nullptr;
			}
		}
	}
    B->removeFromParent();
	
}

Building* BuildingManager::CreateEnemyBuilding(int BuildingTypeName)
{
	Building* B = NULL;
	Sprite* spr = NULL;
	if (BuildingTypeName == BASE)
	{
		B = new Base();
		spr = Sprite::createWithSpriteFrameName("Base.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == BARRACK)
	{
		B = new Barrack();
		spr = Sprite::createWithSpriteFrameName("Barrack.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == MINE)
	{
		B = new Mine();
		spr = Sprite::createWithSpriteFrameName("Mine.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == POWERSTATION)
	{
		B = new PowerStation();
		spr = Sprite::createWithSpriteFrameName("PowerStation.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == FACTORY)
	{
		B = new Factory();
		spr = Sprite::createWithSpriteFrameName("Factory.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else
	{
		return NULL;
	}
	B->autorelease();
	B->_hpBar = Sprite::createWithSpriteFrameName("RedBar.png");
	B->addChild(B->_hpBar);
	B->_hpBar->setContentSize(Size(200, 5));
	B->_hpBar->setPosition(130, 220);
	B->_hpBar->setGlobalZOrder(9);
	B->scheduleOnce(schedule_selector(Building::BuildingUpdate), B->_timeToBuild);
	_enemyBuildingMap.insert(std::make_pair(B->GetID(),B));
	return B;
}

void BuildingManager::UpdateMineral(float dt)
{
	GetMineral()->_currentVal +=GetMineralPerSecond();

}

std::unordered_map<int,Building*> BuildingManager::_buildingMap;
std::unordered_map<int,Building*> BuildingManager::_enemyBuildingMap;
int BuildingManager::_mineralPerSecond = 0;
Power* BuildingManager::_pPower;
Mineral* BuildingManager::_pMineral;