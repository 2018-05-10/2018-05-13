#include"BuildingManager.h"
#include"Entity/Building/Base.h"
#include"Entity/Building/Barrack.h"
#include"Entity/Building/Factory.h"
#include"Entity/Building/Mine.h"
#include"Entity/Building/PowerStation.h"
#include"Scene/GameScene/GameScene.h"
USING_NS_CC;

void BuildingManager::SetBaseController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos-static_cast<GameScene*>(this->getParent())->GetMap()->getPosition()))
		{
			
			static_cast<GameScene*>(this->getParent())->GetMenuLayer()->CreateContructionLayer();
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}

void BuildingManager::SetBarrackController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Building*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition()))
		{
			
			static_cast<GameScene*>(this->getParent())->GetMenuLayer()->CreateSoldierLayer(target1->GetBuildingID());
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}

void BuildingManager::SetProducerController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
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

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Building*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition()))
		{
			
			static_cast<GameScene*>(this->getParent())->GetMenuLayer()->CreateFactoryLayer(target1->GetBuildingID());
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
		B = new Base(_pPower, _pMineral, this);
		spr = Sprite::create("Building/Base.png");
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Barrack")
	{
		B = new Barrack(_pPower, _pMineral, this);
		spr = Sprite::create("Building/Barrack.png");
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Mine")
	{
		B = new Mine(_pPower, _pMineral, this);
		spr = Sprite::create("Building/Mine.png");
		B->BindSprite(spr);

	}
	else if (BuildingTypeName == "PowerStation")
	{
		B = new PowerStation(_pPower, _pMineral, this);
		spr = Sprite::create( "Building/PowerStation.png");
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Factory")
	{
		B = new Factory(_pPower, _pMineral, this);
		spr = Sprite::create("Building/Factory.png");
		B->BindSprite(spr);
	}
	else
	{
		return NULL;
	}
	
	_buildingVec.pushBack(B);
	B->_numInVec = _buildingVec.size() - 1;
	int freePower = _pPower->GetAvailableVal();
	if (B->_whatAmI == "Mine")
	{
		UpdateMineralPerSecond();
	}
	if (B->_whatAmI == "PowerStation")
	{
		if (freePower > 0)
		{
			Building* p = NULL;
			for (int i = 0; i < _buildingVec.size(); i++)
			{
				p = _buildingVec.at(i);
				if ((!p->_isWorking) && (p->_powerCost <= freePower))
				{
					freePower -= p->_powerCost;
					p->_isWorking = true;
					_pPower->Use(p->_powerCost);
				}
			}
		}
	}

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
	return 	static_cast<GameScene*>(this->getParent())->GetMap();
}
SoldierManager*  BuildingManager::GetSoldierManager()
{
	return  static_cast<GameScene*>(this->getParent())->GetSoldierManager();
}
MapManager* BuildingManager::GetMapManager()
{
	return static_cast<GameScene*>(this->getParent())->GetMapManager();
}
Mineral* BuildingManager::GetMineral()
{
	return  static_cast<GameScene*>(this->getParent())->GetMineral();
}
Power* BuildingManager::GetPower()
{
	return  static_cast<GameScene*>(this->getParent())->GetPower();
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