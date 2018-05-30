#include"MenuLayer.h"
#include"GameScene.h"
#include"Entity/Building/Base.h"
#include"Entity/Building/Barrack.h"
#include"Entity/Building/Mine.h"
#include"Entity/Building/PowerStation.h"
#include"extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
#include"Manager/BuildingManager.h"
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
	this->ClearLayer();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	menuLayer->setContentSize(Size(visibleSize.width*0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	menuLayer->setPosition(visibleSize.width*0.7, 0);
	
	this->addChild(menuLayer);
}
void  MenuLayer::CreateContructionLayer()
{
	this->ClearLayer();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	menuLayer->setContentSize(Size(visibleSize.width *0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	menuLayer->setPosition(visibleSize.width*0.7, 0);

	auto contentSize = menuLayer->getContentSize();

	auto base =Sprite::create("Building/Base.png");
	base->setPosition(Point(contentSize.width / 4, contentSize.height  /2));
	base->setContentSize(Size(0.6*base->getContentSize().width, 0.6*base->getContentSize().height));
	menuLayer->addChild(base);
	_buildings.push_back(base);
	
	auto barrack= Sprite::create("Building/Factory.png");
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


	this->SetBuildingListController();

	this->addChild(menuLayer);
}

void MenuLayer::CreateSoldierLayer()
{
	this->ClearLayer();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	menuLayer->setContentSize(Size(visibleSize.width *0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	menuLayer->setPosition(visibleSize.width*0.7, 0);
	this->addChild(menuLayer);
}

void MenuLayer::SetBuildingListController()
{
	this->SetBaseConstructionController();
	this->SetBarrackConstructionController();
	this->SetMineConstructionController();
	this->SetPowerStationController();
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
			_target->BindSprite(Sprite::createWithSpriteFrame(_buildings[0]->getSpriteFrame()));
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 1);
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
		_target->GetSprite()->setColor(Color3B::GREEN);
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		_target->GetSprite()->setOpacity(255);
		_target->GetSprite()->setColor(Color3B(255, 255, 255));
		_buildings[0]->setColor(Color3B(255, 255, 255));
		static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetBaseController(_target);
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
			_target->BindSprite(Sprite::createWithSpriteFrame(_buildings[1]->getSpriteFrame()));
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 2);
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
		_target->GetSprite()->setColor(Color3B::GREEN);

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		_target->GetSprite()->setOpacity(255);
		_target->GetSprite()->setColor(Color3B(255, 255, 255));
		_buildings[1]->setColor(Color3B(255, 255, 255));
		static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetBarrackController(_target);
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
			_target->BindSprite(Sprite::createWithSpriteFrame(_buildings[2]->getSpriteFrame()));
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 3);
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
		_target->GetSprite()->setColor(Color3B::GREEN);

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		_target->GetSprite()->setOpacity(255);
		_target->GetSprite()->setColor(Color3B(255, 255, 255));
		_buildings[2]->setColor(Color3B(255, 255, 255));
		static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetProducerController(_target);
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
			_target = Mine::create();
			_target->BindSprite(Sprite::createWithSpriteFrame(_buildings[3]->getSpriteFrame()));
			_target->GetSprite()->setOpacity(100);
			static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 4);
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
		_target->GetSprite()->setColor(Color3B::GREEN);

	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{
		_target->GetSprite()->setOpacity(255);
		_target->GetSprite()->setColor(Color3B(255, 255, 255));
		_buildings[3]->setColor(Color3B(255, 255, 255));
		static_cast<GameScene*>(this->getParent())->GetBuildingManager()->SetProducerController(_target);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _buildings[3]);
}