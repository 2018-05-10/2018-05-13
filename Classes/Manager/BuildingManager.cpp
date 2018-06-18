#include"BuildingManager.h"
#include"Entity/Building/Base.h"
#include"Entity/Building/Barrack.h"
#include"Entity/Building/Factory.h"
#include"Entity/Building/Mine.h"
#include"Entity/Building/PowerStation.h"
#include"Scene/GameScene/GameScene.h"
#include"Scene/GameScene/MenuLayer.h"

USING_NS_CC;

void BuildingManager::SetBaseController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&,building](Touch *touch, Event *event)
	{
		
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos-static_cast<GameScene*>(this->getParent())->GetMap()->getPosition()))
		{
			if (!building->IsWorking())
			{
				GetMenuLayer()->CreateMainLayer();
			}
			else
			{
				GetMenuLayer()->CreateContructionLayer();
			}
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}

void BuildingManager::SetBarrackController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&, building](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Building*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos - GetMap()->getPosition()))
		{
			if (!building->IsWorking())
			{
				GetMenuLayer()->CreateMainLayer();
			}
			else
			{
				GetMenuLayer()->CreateSoldierLayer(target1->GetBuildingID());
			}
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}

void BuildingManager::SetProducerController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&, building](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition()))
		{
			
			static_cast<GameScene*>(this->getParent())->GetMenuLayer()->CreateMainLayer();
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}

void BuildingManager::SetFactoryController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&, building](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Building*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos - GetMap()->getPosition()))
		{
			if (!building->IsWorking())
			{
				GetMenuLayer()->CreateMainLayer();
			}
			else
			{
				GetMenuLayer()->CreateFactoryLayer(building->GetBuildingID());
				
			}
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}

Building* BuildingManager::CreateBuilding(char* BuildingTypeName)
{
	Building* B = NULL;
	Sprite* spr = NULL;
	if (BuildingTypeName == "Base")
	{
		B = new Base(_pPower, _pMineral,0);
		spr = Sprite::createWithSpriteFrameName("Base.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == "Barrack")
	{
		B = new Barrack(_pPower, _pMineral, 0);
		spr = Sprite::createWithSpriteFrameName("Barrack.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Mine")
	{
		B = new Mine(_pPower, _pMineral,0);
		spr = Sprite::createWithSpriteFrameName("Mine.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == "PowerStation")
	{
		B = new PowerStation(_pPower, _pMineral,0);
		spr = Sprite::createWithSpriteFrameName( "PowerStation.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Factory")
	{
		B = new Factory(_pPower, _pMineral, 0);
		spr = Sprite::createWithSpriteFrameName("Factory.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	
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
	B->_timeBar= Sprite::createWithSpriteFrameName("BlueBar.png");
	B->addChild(B->_timeBar);
	B->_timeBar->setContentSize(Size(200, 5));
	B->_timeBar->setPosition(130, 240);
	B->_timeBar->setScaleX(0);
	B->scheduleUpdate();
	B->scheduleOnce(schedule_selector(Building::BuildingUpdate), B->_timeToBuild);
	_buildingVec.push_back(B);
	B->_numInVec = _buildingVec.size() - 1;

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
	Building* p = NULL;
	for (int i = 0; i < _buildingVec.size(); ++i)
	{
		p = _buildingVec.at(i);
		if ((p->_whatAmI == "Mine") && (p->_isWorking))
		{
			val += p->_mineralProducePerSecond;
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
	case(0):
		mineralCost =0 ;
		powerCost =40 ;
		break;
	case(1):
		mineralCost = 100;
		powerCost =35 ;
		break;
	case(2):
		mineralCost =100 ;
		powerCost = 35;
		break;
	case(3):
		mineralCost = 50;
		powerCost =25 ;
		break;
	case(4):
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
	if (B->_whatAmI == "PowerStation"&&!B->_player)
	{
		int freePower = _pPower->GetAvailableVal();
		while (true)
		{
			int i = _buildingVec.size() - 1;
			if (freePower < 0)
			{
				Building* p = _buildingVec.at(i);
				if (p != NULL)
				{
					p->_isWorking = false;
					freePower += p->_powerCost;
				}
				--i;
			}
			else
			{
				break;
			}
		}
	}
	if (B->_whatAmI == "Mine" && !B->_player)
	{
		UpdateMineralPerSecond();
	}
	if (B->_player)
	{
		_enemyBuildingVec[B->_numInVec] = nullptr;
	}
    B->removeFromParent();
	
}

Building* BuildingManager::CreateEnemyBuilding(char* BuildingTypeName)
{
	Building* B = NULL;
	Sprite* spr = NULL;
	if (BuildingTypeName == "Base")
	{
		B = new Base();
		spr = Sprite::createWithSpriteFrameName("Base.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == "Barrack")
	{
		B = new Barrack();
		spr = Sprite::createWithSpriteFrameName("Barrack.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Mine")
	{
		B = new Mine();
		spr = Sprite::createWithSpriteFrameName("Mine.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == "PowerStation")
	{
		B = new PowerStation();
		spr = Sprite::createWithSpriteFrameName("PowerStation.png");
		spr->setColor(Color3B(100, 100, 100));
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Factory")
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
	B->scheduleOnce(schedule_selector(Building::BuildingUpdate), B->_timeToBuild);
	_enemyBuildingVec.push_back(B);
	B->_numInVec = _enemyBuildingVec.size() - 1;
	return B;
}

std::vector<Building*> BuildingManager::_buildingVec;
std::vector<Building*> BuildingManager::_enemyBuildingVec;
int BuildingManager::_mineralPerSecond = 0;
Power* BuildingManager::_pPower;
Mineral* BuildingManager::_pMineral;