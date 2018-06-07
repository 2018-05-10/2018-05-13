#include"MenuLayer.h"
#include"GameScene.h"
#include"Entity/Building/Base.h"
#include"Entity/Building/Barrack.h"
#include"Entity/Building/Mine.h"
#include"Entity/Building/PowerStation.h"
#include"Entity/Building/Factory.h"
#include"Entity/Soldier/Tank.h"
#include"SimpleAudioEngine.h"
#include"extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
#include"Manager/BuildingManager.h"
#include"Manager/SoldierManager.h"
#include"Manager/MapManager.h"

USING_NS_CC;
using namespace extension;
using namespace ui;

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->CreateMainLayer();
	
	return true;
}

void MenuLayer::CreateMainLayer()
{
	auto menuLayer = CreateLayer();
	
	this->addChild(menuLayer);
}
void  MenuLayer::CreateContructionLayer()
{
	
	auto menuLayer = CreateLayer();
	auto contentSize = menuLayer->getContentSize();

	auto base =Sprite::create("Building/Base.png");
	base->setPosition(Point(contentSize.width / 2, contentSize.height  *3/8));
	base->setContentSize(Size(0.6*base->getContentSize().width, 0.6*base->getContentSize().height));
	menuLayer->addChild(base);
	_buildings.push_back(base);
	
	auto barrack= Sprite::create("Building/Barrack.png");
	barrack->setPosition(contentSize.width *3/4, contentSize.height  /2);
	barrack->setContentSize(Size(0.6*barrack->getContentSize().width, 0.6*barrack->getContentSize().height));
	menuLayer->addChild(barrack);
	_buildings.push_back(barrack);

	auto mine = Sprite::create("Building/Mine.png");
	mine->setPosition(contentSize.width * 1 / 4, contentSize.height /4);
	mine->setContentSize(Size(0.6*mine->getContentSize().width, 0.6*mine->getContentSize().height));
	menuLayer->addChild(mine);
	_buildings.push_back(mine);

	auto powerStation = Sprite::create("Building/powerStation.png");
	powerStation->setPosition(contentSize.width * 3 / 4, contentSize.height / 4);
	powerStation->setContentSize(Size(0.6*powerStation->getContentSize().width, 0.6*powerStation->getContentSize().height));
	menuLayer->addChild(powerStation);
	_buildings.push_back(powerStation);

	auto factory = Sprite::create("Building/Factory.png");
	factory->setPosition(contentSize.width / 4, contentSize.height / 2);
	factory->setContentSize(Size(0.6*factory->getContentSize().width, 0.6*factory->getContentSize().height));
	menuLayer->addChild(factory);
	_buildings.push_back(factory);

	this->SetBuildingListController();

	this->addChild(menuLayer);
}

void MenuLayer::CreateSoldierLayer(int buildingID)
{
	auto menuLayer = CreateLayer();
	auto contentSize = menuLayer->getContentSize();

	

	this->addChild(menuLayer);
}

void MenuLayer::CreateFactoryLayer(int buildingID)
{
	auto menuLayer = CreateLayer();
	auto contentSize = menuLayer->getContentSize();

	auto tank = Button::create("tankpicture.png");
	tank->setScale(3.0);
	tank->setPosition(Size(contentSize.width / 4, contentSize.height / 2));


	tank->addTouchEventListener([&,buildingID](Ref*, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:

			if (GetSoldierManager()->CheckSoldierResource("Tank"))
			{
				Building* building = static_cast<Building*>(GetMap()->getChildByTag(buildingID));
				auto pos = building->getPosition();
				auto tilePos = GetMapManager()->ChangeToTiledPos(pos);
				auto tank1 = GetSoldierManager()->CreateSoldier("Tank");
				GetMap()->addChild(tank1, 6);
				auto landPos = GetMapManager()->BFS(pos);
				tank1->setPosition(landPos);
				GetSoldierManager()->SetSoldierController(tank1);
				GetMapManager()->SetSoldier(landPos);
				break;
			}
			else
			{
				log("not enough mineral");
			}
		}
	});

	menuLayer->addChild(tank);
	
	this->addChild(menuLayer);
}

void MenuLayer::SetBuildingListController()
{
	this->SetBaseConstructionController();
	this->SetBarrackConstructionController();
	this->SetMineConstructionController();
	this->SetPowerStationController();
	this->SetFactoryController();
}

void MenuLayer::ClearLayer()
{
	_buildings.clear();
	this->removeAllChildren();
}

void MenuLayer::SetBaseConstructionController()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		if (target1->getBoundingBox().containsPoint(pos - Point(visibleSize.width*0.7, 0)))
		{
			_target = Sprite::create("Building/Base.png");
			_target->setOpacity(100);
			GetMap()->addChild(_target, 1);
			auto worldPos = Point(_buildings[0]->getPosition().x + visibleSize.width*0.7, _buildings[0]->getPosition().y)-GetMap()->getPosition();
			_target->setPosition(worldPos);
			_buildings[0]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos -GetMap()->getPosition());
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),0)&&GetBuildingManager()->BuildingResourceCheck(0))
		{
			_target->setColor(Color3B::GREEN);
		}
		else
		{
			_target->setColor(Color3B::RED);
		}
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(), 0) && GetBuildingManager()->BuildingResourceCheck(0))
	{
		_target->removeFromParent();
		auto building = GetBuildingManager()->CreateBuilding("Base");
		auto setPos =GetMapManager()->ChangeToTiledPos(originPos - GetMap()->getPosition());
		GetMap()->addChild(building, setPos.x + setPos.y, Building::buildingsID);
		setPos =GetMapManager()->ChangeToCocosPos(setPos);
		building->setPosition(setPos);
		GetMapManager()->SetBuilding(setPos,0);
		GetBuildingManager()->SetBaseController(building);

		log("%f %f",GetMapManager()->ChangeToTiledPos(setPos +building->getContentSize() / 2).x,
			GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).y);
	}
		else
	{
		_target->removeFromParent();
	}
		_buildings[0]->setColor(Color3B(255, 255, 255));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _buildings[0]);
}

void MenuLayer::SetBarrackConstructionController()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		Point pos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (target1->getBoundingBox().containsPoint(pos - Point(visibleSize.width*0.7, 0)))
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			_target = Sprite::create("Building/Barrack.png");
			_target->setOpacity(100);
			GetMap()->addChild(_target, 1);
			auto worldPos = Point(_buildings[1]->getPosition().x + visibleSize.width*0.7, _buildings[1]->getPosition().y)-GetMap()->getPosition();
			_target->setPosition(worldPos);
			_buildings[1]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos -GetMap()->getPosition());
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),2) && GetBuildingManager()->BuildingResourceCheck(2))
		{
			_target->setColor(Color3B::GREEN);
		}
		else
		{
			_target->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),2) && GetBuildingManager()->BuildingResourceCheck(2))
		{

			_target->removeFromParent();
			auto building = GetBuildingManager()->CreateBuilding("Barrack");
			auto setPos = GetMapManager()->ChangeToTiledPos(originPos - GetMap()->getPosition());
			GetMap()->addChild(building, setPos.x + setPos.y, Building::buildingsID);
			setPos = GetMapManager()->ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			GetMapManager()->SetBuilding(setPos, 2);
			GetBuildingManager()->SetBarrackController(building);

			log("%f %f", GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).x,
				GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).y);
			
		}
		else
		{
			_target->removeFromParent();
		}
		_buildings[1]->setColor(Color3B(255, 255, 255));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _buildings[1]);
}

void MenuLayer::SetMineConstructionController()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		Point pos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (target1->getBoundingBox().containsPoint(pos - Point(visibleSize.width*0.7, 0)))
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			_target = Sprite::create("Building/Mine.png");
			_target->setOpacity(100);
			GetMap()->addChild(_target, 3);
			auto worldPos = Point(_buildings[2]->getPosition().x + visibleSize.width*0.7, _buildings[2]->getPosition().y)
				-GetMap()->getPosition();
			_target->setPosition(worldPos);
			_buildings[2]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos -GetMap()->getPosition());
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),3) && GetBuildingManager()->BuildingResourceCheck(3))
		{
			_target->setColor(Color3B::GREEN);
		}
		else
		{
			_target->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),3) && GetBuildingManager()->BuildingResourceCheck(3))
		{

			_target->removeFromParent();
			auto building = GetBuildingManager()->CreateBuilding("Mine");
			auto setPos = GetMapManager()->ChangeToTiledPos(originPos - GetMap()->getPosition());
			GetMap()->addChild(building, setPos.x + setPos.y, Building::buildingsID);
			setPos = GetMapManager()->ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			GetMapManager()->SetBuilding(setPos,3);
			GetBuildingManager()->SetProducerController(building);

			log("%f %f", GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).x,
				GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).y);
		}
		else
		{
			_target->removeFromParent();

		}
		_buildings[2]->setColor(Color3B(255, 255, 255));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _buildings[2]);
}

void MenuLayer::SetPowerStationController()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		Point pos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (target1->getBoundingBox().containsPoint(pos - Point(visibleSize.width*0.7, 0)))
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			_target =Sprite::create("Building/PowerStation.png");
			
			_target->setOpacity(100);
			GetMap()->addChild(_target, 4);
			auto worldPos = Point(_buildings[3]->getPosition().x + visibleSize.width*0.7, _buildings[3]->getPosition().y)
				-GetMap()->getPosition();
			_target->setPosition(worldPos);
			_buildings[3]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos -GetMap()->getPosition());
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),4) && GetBuildingManager()->BuildingResourceCheck(4))
		{
			_target->setColor(Color3B::GREEN);
		}
		else
		{
			_target->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),4) && GetBuildingManager()->BuildingResourceCheck(4))
		{

			_target->removeFromParent();
			auto building = GetBuildingManager()->CreateBuilding("PowerStation");
			auto setPos = GetMapManager()->ChangeToTiledPos(originPos - GetMap()->getPosition());
			GetMap()->addChild(building, setPos.x + setPos.y, Building::buildingsID);
			setPos = GetMapManager()->ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			GetMapManager()->SetBuilding(setPos,4);
			GetBuildingManager()->SetProducerController(building);

			log("%f %f", GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).x,
				GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).y);
		}
		else
		{
			_target->removeFromParent();
		}
		_buildings[3]->setColor(Color3B(255, 255, 255));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _buildings[3]);
}

void MenuLayer::SetFactoryController()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		Point pos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (target1->getBoundingBox().containsPoint(pos - Point(visibleSize.width*0.7, 0)))
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			_target = Sprite::create("Building/Factory.png");
			_target->setOpacity(100);
			GetMap()->addChild(_target, 5);
			auto worldPos = Point(_buildings[4]->getPosition().x + visibleSize.width*0.7, _buildings[4]->getPosition().y)-GetMap()->getPosition();
			_target->setPosition(worldPos);
			_buildings[4]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos -GetMap()->getPosition());
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),1) && GetBuildingManager()->BuildingResourceCheck(1))
		{
			_target->setColor(Color3B::GREEN);
		}
		else
		{
			_target->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (GetMapManager()->BuildingPositionCheck(originPos -GetMap()->getPosition(),1) && GetBuildingManager()->BuildingResourceCheck(1))
		{

			_target->removeFromParent();
			auto building = GetBuildingManager()->CreateBuilding("Factory");
			auto setPos = GetMapManager()->ChangeToTiledPos(originPos - GetMap()->getPosition());
			GetMap()->addChild(building, setPos.x + setPos.y, Building::buildingsID);
			setPos = GetMapManager()->ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			GetMapManager()->SetBuilding(setPos,1);
			GetBuildingManager()->SetFactoryController(building);

			log("%f %f", GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).x,
				GetMapManager()->ChangeToTiledPos(setPos + building->getContentSize() / 2).y);
		}
		else
		{
			_target->removeFromParent();
		}
		_buildings[4]->setColor(Color3B(255, 255, 255));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _buildings[4]);
}

Layer* MenuLayer::CreateLayer()
{
	this->ClearLayer();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));

	menuLayer->setContentSize(Size(visibleSize.width *0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	menuLayer->setPosition(visibleSize.width*0.7, 0);

	CreateMusicButton();

	return menuLayer;
}

void MenuLayer::CreateMusicButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto music_button = MenuItemImage::create("music.png", "nomusic.png");
	auto pause_button = MenuItemImage::create("nomusic.png", "music.png");

	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer::MenuMusicCallBack, this), music_button, pause_button, NULL);
	toggleItem->setScale(1.0f);
	toggleItem->setPosition(Point(visibleOrigin.x + visibleSize.width * 0.97, visibleOrigin.y + visibleSize.height * 0.05));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,5);
}

void MenuLayer::MenuMusicCallBack(cocos2d::Ref* pSender)
{
	if (_musicOn)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

		_musicOn = false;
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

		_musicOn = true;
	}
}

TMXTiledMap* MenuLayer::GetMap()
{
	return 	static_cast<GameScene*>(this->getParent())->GetMap();
}
BuildingManager*  MenuLayer::GetBuildingManager()
{
	return  static_cast<GameScene*>(this->getParent())->GetBuildingManager();
}

MapManager* MenuLayer::GetMapManager()
{
	return static_cast<GameScene*>(this->getParent())->GetMapManager();
}
SoldierManager* MenuLayer::GetSoldierManager()
{
	return static_cast<GameScene*>(this->getParent())->GetSoldierManager();
}