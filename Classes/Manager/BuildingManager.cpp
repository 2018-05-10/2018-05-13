#include"BuildingManager.h"
#include"Entity/Building/Base.h"
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
			log("%d", target1->GetBuildingID());
			static_cast<GameScene*>(this->getParent())->GetMenuLayer()->CreateFactoryLayer(target1->GetBuildingID());
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}