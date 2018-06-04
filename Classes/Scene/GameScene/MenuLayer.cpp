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
			Building* building = static_cast<Building*>(static_cast<GameScene*>(this->getParent())->GetMap()->getChildByTag(buildingID));
			auto pos = building->getPosition()+building->getContentSize()/2;
			auto tilePos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(pos);
			auto tank1 = SoldierManager::CreateSoldier("Tank");
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(tank1,6);
			auto landPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->BFS(pos-_target->getContentSize()/2);
			tank1->setPosition(landPos);
			static_cast<GameScene*>(this->getParent())->GetSoldierManager()->SetSoldierController(tank1);
			static_cast<GameScene*>(this->getParent())->GetMapManager()->SetSoldier(landPos);
			break;
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
			_target = Base::create();
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 1, _target->GetBuildingID());
			auto worldPos = Point(_buildings[0]->getPosition().x + visibleSize.width*0.7, _buildings[0]->getPosition().y)
				- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
			_target->setPosition(worldPos - _target->getContentSize() / 2);
			_buildings[0]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() - _target->getContentSize() / 2);
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),0))
		{
			_target->GetSprite()->setColor(Color3B::GREEN);
		}
		else
		{
			_target->GetSprite()->setColor(Color3B::RED);
		}
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(), 0))
	{
		auto setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition()-_target->getContentSize()/2);
		_target->setZOrder(setPos.x + setPos.y);
		setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToCocosPos(setPos);
		_target->setPosition(setPos);
		
		_target->GetSprite()->setOpacity(255);
		_target->GetSprite()->setColor(Color3B(255, 255, 255));
		static_cast<GameScene*>(this->getParent())->GetMapManager()->SetBuilding(
			originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(), 0);
		static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetBaseController(_target);

		log("%f %f", static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).x,
			static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).y);
	}
		else
	{
		_target->removeFromParent();
		--Building::buildingsID;
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
			_target = Barrack::create();
			
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 2, _target->GetBuildingID());
			auto worldPos = Point(_buildings[1]->getPosition().x + visibleSize.width*0.7, _buildings[1]->getPosition().y)
				- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
			_target->setPosition(worldPos - _target->getContentSize() / 2);
			_buildings[1]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() -
			_target->getContentSize() / 2);
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),2))
		{
			_target->GetSprite()->setColor(Color3B::GREEN);
		}
		else
		{
			_target->GetSprite()->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),2))
		{

			auto setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(originPos -
				static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() - _target->getContentSize() / 2);
			_target->setZOrder(setPos.x + setPos.y);
			setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToCocosPos(setPos);
			_target->setPosition(setPos);
		
			_target->GetSprite()->setOpacity(255);
			_target->GetSprite()->setColor(Color3B(255, 255, 255));
			static_cast<GameScene*>(this->getParent())->GetMapManager()->SetBuilding(
				originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),2);
			static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetBarrackController(_target);
			log("%f %f", static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).x,
				static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).y);
			
		}
		else
		{
			_target->removeFromParent();
			--Building::buildingsID;
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
			_target = Mine::create();
			
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 3,_target->GetBuildingID());
			auto worldPos = Point(_buildings[2]->getPosition().x + visibleSize.width*0.7, _buildings[2]->getPosition().y)
				- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
			_target->setPosition(worldPos - _target->getContentSize() / 2);
			_buildings[2]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() -
			_target->getContentSize() / 2);
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),3))
		{
			_target->GetSprite()->setColor(Color3B::GREEN);
		}
		else
		{
			_target->GetSprite()->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(
			originPos -static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),3))
		{

			auto setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(originPos -
				static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() - _target->getContentSize() / 2);
			_target->setZOrder(setPos.x + setPos.y);
			setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToCocosPos(setPos);
			_target->setPosition(setPos);
		
			_target->GetSprite()->setOpacity(255);
			_target->GetSprite()->setColor(Color3B(255, 255, 255));
			static_cast<GameScene*>(this->getParent())->GetMapManager()->SetBuilding(
				originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),3);
			static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetProducerController(_target);
			log("%f %f", static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).x,
				static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).y);
		}
		else
		{
			_target->removeFromParent();
			--Building::buildingsID;
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
			_target = PowerStation::create();
			
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 4, _target->GetBuildingID());
			auto worldPos = Point(_buildings[3]->getPosition().x + visibleSize.width*0.7, _buildings[3]->getPosition().y)
				- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
			_target->setPosition(worldPos - _target->getContentSize() / 2);
			_buildings[3]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() -
			_target->getContentSize() / 2);
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),4))
		{
			_target->GetSprite()->setColor(Color3B::GREEN);
		}
		else
		{
			_target->GetSprite()->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),4))
		{

			auto setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(originPos -
				static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() - _target->getContentSize() / 2);
			_target->setZOrder(setPos.x + setPos.y);
			setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToCocosPos(setPos);
			_target->setPosition(setPos);
			
			_target->GetSprite()->setOpacity(255);
			_target->GetSprite()->setColor(Color3B(255, 255, 255));
			static_cast<GameScene*>(this->getParent())->GetMapManager()->SetBuilding(
				originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),4);
			static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetProducerController(_target);
			log("%f %f", static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).x,
				static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).y);
		}
		else
		{
			_target->removeFromParent();
			--Building::buildingsID;
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
			_target = Factory::create();

			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 5, _target->GetBuildingID());
			auto worldPos = Point(_buildings[4]->getPosition().x + visibleSize.width*0.7, _buildings[4]->getPosition().y)
				- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
			_target->setPosition(worldPos - _target->getContentSize() / 2);
			_buildings[4]->setColor(Color3B(100, 100, 100));

			return true;
		}
		return false;
	};
	listener->onTouchMoved = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_target->setPosition(originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() -
			_target->getContentSize() / 2);
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),1))
		{
			_target->GetSprite()->setColor(Color3B::GREEN);
		}
		else
		{
			_target->GetSprite()->setColor(Color3B::RED);
		}

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		if (static_cast<GameScene*>(this->getParent())->GetMapManager()->BuildingCheck(originPos -
			static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),1))
		{

			auto setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(originPos -
				static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() - _target->getContentSize() / 2);
			_target->setZOrder(setPos.x + setPos.y);
			setPos = static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToCocosPos(setPos);
			_target->setPosition(setPos);
			
			_target->GetSprite()->setOpacity(255);
			_target->GetSprite()->setColor(Color3B(255, 255, 255));
			static_cast<GameScene*>(this->getParent())->GetMapManager()->SetBuilding(
				originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition(),1);
			static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetFactoryController(_target);
			log("%f %f", static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).x,
				static_cast<GameScene*>(this->getParent())->GetMapManager()->ChangeToTiledPos(setPos + _target->getContentSize() / 2).y);
		}
		else
		{
			_target->removeFromParent();
			--Building::buildingsID;
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