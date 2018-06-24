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
#include"Tool/FlowWord.h"

USING_NS_CC;
using namespace extension;
using namespace ui;

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_layer=CreateLayer();

	this->addChild(_layer);
	this->schedule(schedule_selector(MenuLayer::update), 0.2f);
	
	return true;
}

void MenuLayer::CreateMainLayer()
{
	this->ClearLayer();
	
}
void  MenuLayer::CreateContructionLayer()
{
	
	auto menuLayer = Layer::create();
	this->ClearLayer();
	menuLayer->setContentSize(Size(480, 900));
	auto contentSize = menuLayer->getContentSize();

	

	auto base = Sprite::createWithSpriteFrameName("Base.png");
	base->setPosition(Point(contentSize.width / 2, contentSize.height  *3/8));
	base->setContentSize(Size(0.6*base->getContentSize().width, 0.6*base->getContentSize().height));
	menuLayer->addChild(base);
	_buildings.push_back(base);
	
	auto barrack= Sprite::createWithSpriteFrameName("Barrack.png");
	barrack->setPosition(contentSize.width *3/4, contentSize.height  /2);
	barrack->setContentSize(Size(0.6*barrack->getContentSize().width, 0.6*barrack->getContentSize().height));
	menuLayer->addChild(barrack);
	_buildings.push_back(barrack);

	auto mine = Sprite::createWithSpriteFrameName("Mine.png");
	mine->setPosition(contentSize.width * 1 / 4, contentSize.height /4);
	mine->setContentSize(Size(0.6*mine->getContentSize().width, 0.6*mine->getContentSize().height));
	menuLayer->addChild(mine);
	_buildings.push_back(mine);

	auto powerStation = Sprite::createWithSpriteFrameName("PowerStation.png");
	powerStation->setPosition(contentSize.width * 3 / 4, contentSize.height / 4);
	powerStation->setContentSize(Size(0.6*powerStation->getContentSize().width, 0.6*powerStation->getContentSize().height));
	menuLayer->addChild(powerStation);
	_buildings.push_back(powerStation);

	auto factory = Sprite::createWithSpriteFrameName("Factory.png");
	factory->setPosition(contentSize.width / 4, contentSize.height / 2);
	factory->setContentSize(Size(0.6*factory->getContentSize().width, 0.6*factory->getContentSize().height));
	menuLayer->addChild(factory);
	_buildings.push_back(factory);

	this->SetBuildingListController();

	_layer->addChild(menuLayer,1,1);
}

void MenuLayer::CreateSoldierLayer(int buildingID)
{

	auto menuLayer = Layer::create();
	this->ClearLayer();
	menuLayer->setContentSize(Size(480, 900));
	auto contentSize = menuLayer->getContentSize();

	_buildingListUI = GUIReader::getInstance()->widgetFromJsonFile("UI/BuildingListUi_1.ExportJson");
	menuLayer->addChild(_buildingListUI);
	auto lab = static_cast<Text*>(Helper::seekWidgetByName(_buildingListUI, "Number"));
	lab->setText(Value(static_cast<Barrack*>(GetMap()->getChildByTag(buildingID))->_buildingList.size()).asString());

	auto soldier = Button::create("soldierpicture.png");
	soldier->setScale(0.4);
	soldier->setPosition(Size(contentSize.width / 4, contentSize.height / 2));

	soldier->addTouchEventListener([&, buildingID](Ref*, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:

			if (GetSoldierManager()->CheckSoldierResource("Infantry"))
			{
				auto building = static_cast<Barrack*>(GetMap()->getChildByTag(buildingID));
				building->_buildingList.push("Infantry");
				GetMineral()->Cost(20);
				auto lab = static_cast<Text*>(Helper::seekWidgetByName(_buildingListUI, "Number"));
				lab->setText(Value(building->_buildingList.size()).asString());
				break;
			}
			else
			{
				auto flowWord = FlowWord::create();
				this->getParent()->addChild(flowWord);
				flowWord->showWord("not enough resource", Point(900, 700),0.5,2);
				break;
			}
		}
	});
	
	menuLayer->addChild(soldier);

	auto dog = Button::create("dogpicture.png");
	dog->setScale(0.3);
	dog->setPosition(Size(contentSize.width *3/ 4, contentSize.height / 2));

	dog->addTouchEventListener([&, buildingID](Ref*, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:

			if (GetSoldierManager()->CheckSoldierResource("Dog"))
			{
				auto building = static_cast<Barrack*>(GetMap()->getChildByTag(buildingID));
				building->_buildingList.push("Dog");
				GetMineral()->Cost(10);
				auto lab = static_cast<Text*>(Helper::seekWidgetByName(_buildingListUI, "Number"));
				lab->setText(Value(building->_buildingList.size()).asString());
				break;
			}
			else
			{
				auto flowWord = FlowWord::create();
				this->getParent()->addChild(flowWord);
				flowWord->showWord("not enough resource", Point(900, 700),0.5,2);
				break;
			}
		}
	});

	menuLayer->addChild(dog);

	_layer->addChild(menuLayer,1,1);

}

void MenuLayer::CreateFactoryLayer(int buildingID)
{

	
	auto menuLayer = Layer::create();
	this->ClearLayer();
	menuLayer->setContentSize(Size(480, 900));
	auto contentSize = menuLayer->getContentSize();

	_buildingListUI = GUIReader::getInstance()->widgetFromJsonFile("UI/BuildingListUi_1.ExportJson");
	menuLayer->addChild(_buildingListUI);
	auto lab = static_cast<Text*>(Helper::seekWidgetByName(_buildingListUI, "Number"));
	lab->setText(Value(static_cast<Barrack*>(GetMap()->getChildByTag(buildingID))->_buildingList.size()).asString()); 

	auto tank = Button::create("tankpicture.png");
	tank->setScale(0.3);
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
				auto building = static_cast<Factory*>(GetMap()->getChildByTag(buildingID));
				building->_buildingList.push("Tank");
				GetMineral()->Cost(50);
				auto lab=static_cast<Text*>(Helper::seekWidgetByName(_buildingListUI, "Number"));
				lab->setText(Value(building->_buildingList.size()).asString());
				break;
			}
			else
			{
				auto flowWord = FlowWord::create();
				this->getParent()->addChild(flowWord);
				flowWord->showWord("not enough resource", Point(900, 700), 0.5, 2);
			}
		}
	});

	menuLayer->addChild(tank);


	
	_layer->addChild(menuLayer,1,1);
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
	_layer->removeChildByTag(1);
	_buildingListUI = nullptr;
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
			_target = Sprite::createWithSpriteFrameName("Base.png");
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),0)&&GetBuildingManager()->BuildingResourceCheck(0))
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(), 0) && GetBuildingManager()->BuildingResourceCheck(0))
	{
		_target->removeFromParent();
		auto building = BuildingManager::CreateBuilding("Base");
		auto setPos =MapManager::ChangeToTiledPos(originPos - GetMap()->getPosition());
		log("%f %f", setPos.x, setPos.y);
		GetMap()->addChild(building, setPos.x+setPos.y, building->GetBuildingID());
		setPos = MapManager::ChangeToCocosPos(setPos);
		building->setPosition(setPos);
		MapManager::SetBuilding(setPos,0);
		GetBuildingManager()->SetBaseController(building);

	
	}
		else
	{
		_target->removeFromParent();
		auto flowWord = FlowWord::create();
		this->getParent()->addChild(flowWord);
		flowWord->showWord("Can't build",Point(900, 700), 0.5, 2);
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
			_target = Sprite::createWithSpriteFrameName("Barrack.png");
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
		if( MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),2) && GetBuildingManager()->BuildingResourceCheck(2))
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),2) && GetBuildingManager()->BuildingResourceCheck(2))
		{

			_target->removeFromParent();
			auto building = BuildingManager::CreateBuilding("Barrack");
			auto setPos = MapManager::ChangeToTiledPos(originPos - GetMap()->getPosition());
			log("%f %f", setPos.x, setPos.y);
			GetMap()->addChild(building, setPos.x + setPos.y, building->GetBuildingID());
			setPos = MapManager::ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			MapManager::SetBuilding(setPos, 2);
			GetBuildingManager()->SetBarrackController(building);

		
			
		}
		else
		{
			_target->removeFromParent();
			auto flowWord = FlowWord::create();
			this->getParent()->addChild(flowWord);
			flowWord->showWord("Can't build", Point(900, 700), 0.5, 2);
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
			_target = Sprite::createWithSpriteFrameName("Mine.png");
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),3) && GetBuildingManager()->BuildingResourceCheck(3))
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),3) && GetBuildingManager()->BuildingResourceCheck(3))
		{

			_target->removeFromParent();
			auto building = BuildingManager::CreateBuilding("Mine");
			auto setPos = MapManager::ChangeToTiledPos(originPos - GetMap()->getPosition());
			log("%f %f", setPos.x, setPos.y);
			GetMap()->addChild(building, setPos.x + setPos.y, building->GetBuildingID());
			setPos = MapManager::ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			MapManager::SetBuilding(setPos,3);
			GetBuildingManager()->SetProducerController(building);

		}
		else
		{
			_target->removeFromParent();
			auto flowWord = FlowWord::create();
			this->getParent()->addChild(flowWord);
			flowWord->showWord("Can't build", Point(900, 700), 0.5, 2);

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
			_target =Sprite::createWithSpriteFrameName("PowerStation.png");
			
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),4) && GetBuildingManager()->BuildingResourceCheck(4))
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),4) && GetBuildingManager()->BuildingResourceCheck(4))
		{

			_target->removeFromParent();
			auto building = BuildingManager::CreateBuilding("PowerStation");
			auto setPos = MapManager::ChangeToTiledPos(originPos - GetMap()->getPosition());
			log("%f %f", setPos.x, setPos.y);
			GetMap()->addChild(building, setPos.x + setPos.y, building->GetBuildingID());
			setPos = MapManager::ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			MapManager::SetBuilding(setPos,4);
			GetBuildingManager()->SetProducerController(building);

			
		}
		else
		{
			_target->removeFromParent();
			auto flowWord = FlowWord::create();
			this->getParent()->addChild(flowWord);
			flowWord->showWord("Can't build", Point(900, 700), 0.5, 2);
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
			_target = Sprite::createWithSpriteFrameName("Factory.png");
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),1) && GetBuildingManager()->BuildingResourceCheck(1))
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
		if (MapManager::BuildingPositionCheck(originPos -GetMap()->getPosition(),1) && GetBuildingManager()->BuildingResourceCheck(1))
		{

			_target->removeFromParent();
			auto building = BuildingManager::CreateBuilding("Factory");
			auto setPos = MapManager::ChangeToTiledPos(originPos - GetMap()->getPosition());
			log("OK");
			GetMap()->addChild(building, setPos.x + setPos.y,building->GetBuildingID());
			setPos = MapManager::ChangeToCocosPos(setPos);
			building->setPosition(setPos);

			MapManager::SetBuilding(setPos,1);
			GetBuildingManager()->SetFactoryController(building);

			
		}
		else
		{
			_target->removeFromParent();
			auto flowWord = FlowWord::create();
			this->getParent()->addChild(flowWord);
			flowWord->showWord("Can't build", Point(900, 700), 0.5, 2);
		}
		_buildings[4]->setColor(Color3B(255, 255, 255));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _buildings[4]);
}

Layer* MenuLayer::CreateLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));

	_resourceUI = GUIReader::getInstance()->widgetFromJsonFile("UI/ResourceUi_1.ExportJson");
	menuLayer->addChild(_resourceUI);
	menuLayer->setContentSize(Size(visibleSize.width *0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	menuLayer->setPosition(visibleSize.width*0.7, 0);

	menuLayer->addChild(CreateMusicButton());

	return menuLayer;
}

Menu* MenuLayer::CreateMusicButton()
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

	return menu;
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
	return 	GameScene::GetMap();
}
BuildingManager*  MenuLayer::GetBuildingManager()
{
	return  	GameScene::GetBuildingManager();
}

MapManager* MenuLayer::GetMapManager()
{
	return 	GameScene::GetMapManager();
}
SoldierManager* MenuLayer::GetSoldierManager()
{
	return 	GameScene::GetSoldierManager();
}
Mineral* MenuLayer::GetMineral()
{
	return 	GameScene::GetMineral();
}
Power* MenuLayer::GetPower()
{
	return	GameScene::GetPower();
}

void MenuLayer::update(float dt)
{
	auto powerBar = static_cast<LoadingBar*>(Helper::seekWidgetByName(_resourceUI, "PowerBar"));
	powerBar->setPercent(100*static_cast<float>(GetPower()->GetAvailableVal()) / static_cast<float>(GetPower()->GetTotalVal()));
	auto mineralBar = static_cast<LoadingBar*>(Helper::seekWidgetByName(_resourceUI, "MineralBar"));
	mineralBar->setPercent(100 * static_cast<float>(GetMineral()->GetCurrentVal()) / 1000);
	auto powerNum= static_cast<Text*>(Helper::seekWidgetByName(_resourceUI, "AllPower"));
	int allPower = GetPower()->GetTotalVal();
	powerNum->setText(Value(allPower).asString());
	auto availablePowerNum= static_cast<Text*>(Helper::seekWidgetByName(_resourceUI, "AvailablePower"));
	int availablePower= GetPower()->GetAvailableVal();
	availablePowerNum->setText(Value(availablePower).asString());
	auto mineralNum = static_cast<Text*>(Helper::seekWidgetByName(_resourceUI, "AllMineral"));
	int allMineral = GetMineral()->GetCurrentVal();
	mineralNum->setText(Value(allMineral).asString());
	auto mineralSpeedNum = static_cast<Text*>(Helper::seekWidgetByName(_resourceUI, "ProduceSpeed"));
	int mineralSpeed = GetBuildingManager()->_mineralPerSecond;
	mineralSpeedNum->setText(Value(mineralSpeed).asString());

}