#include"MenuLayer.h"
#include"GameScene.h"
#include"Entity/Building/Base.h"
#include"extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	menuLayer->setContentSize(Size(visibleSize.width*0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	menuLayer->setPosition(visibleSize.width*0.7, 0);
	
	this->addChild(menuLayer);
}
void  MenuLayer::CreateBaseLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	menuLayer->setContentSize(Size(visibleSize.width *0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	menuLayer->setPosition(visibleSize.width*0.7, 0);

	auto contentSize = menuLayer->getContentSize();

	auto factory =Sprite::create("Building/factory.png");
	factory->setPosition(Point(contentSize.width / 4, contentSize.height * 3 / 4));
	factory->setContentSize(Size(0.6*factory->getContentSize().width, 0.6*factory->getContentSize().height));
	menuLayer->addChild(factory);
	_buildings.push_back(factory);
	
	auto soldier_factory= Sprite::create("Building/soldier_factory.png");
	soldier_factory->setPosition(contentSize.width *3/4, contentSize.height * 3 / 4);
	soldier_factory->setContentSize(Size(0.6*soldier_factory->getContentSize().width, 0.6*soldier_factory->getContentSize().height));
	menuLayer->addChild(soldier_factory);
	_buildings.push_back(soldier_factory);

	this->SetBuildingController();

	this->addChild(menuLayer);
}

void MenuLayer::SetBuildingController()
{
	
		auto listener1 = EventListenerTouchOneByOne::create();
		listener1->setSwallowTouches(true);

		listener1->onTouchBegan = [&](Touch *touch, Event *event)
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
			Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
			if (target1->getBoundingBox().containsPoint(pos-Point(visibleSize.width*0.7,0)))
			{
				auto visibleSize = Director::getInstance()->getVisibleSize();
				_target = Base::create();
				_target->BindSprite( Sprite::createWithSpriteFrame(_buildings[0]->getSpriteFrame()));
				_target->GetSprite()->setOpacity(100);
				static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 2);
				auto worldPos = Point(_buildings[0]->getPosition().x + visibleSize.width*0.7, _buildings[0]->getPosition().y)
					- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
				_target->setPosition(worldPos-_target->getContentSize()/2);

				return true;
			}
			return false;
		};
		listener1->onTouchMoved = [&](Touch* touch, Event* event)
		{
			auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
			_target->setPosition(originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() - _target->getContentSize() / 2);
		};
		listener1->onTouchEnded = [&](Touch* touch, Event* event)
		{
			_target->GetSprite()->setOpacity(255);
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, _buildings[0]);
	
		auto listener2 = EventListenerTouchOneByOne::create();
		listener2->setSwallowTouches(true);

		listener2->onTouchBegan = [&](Touch *touch, Event *event)
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
			Point pos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
			if (target1->getBoundingBox().containsPoint(pos - Point(visibleSize.width*0.7, 0)))
			{
				auto visibleSize = Director::getInstance()->getVisibleSize();
				_target = Base::create();
				_target ->BindSprite(Sprite::createWithSpriteFrame(_buildings[1]->getSpriteFrame()));
				_target->GetSprite()->setOpacity(100);
				static_cast<GameScene*>(this->getParent())->GetMap()->addChild(_target, 2);
				auto worldPos = Point(_buildings[1]->getPosition().x + visibleSize.width*0.7, _buildings[1]->getPosition().y)
					- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
				_target->setPosition(worldPos - _target->getContentSize() / 2);

				return true;
			}
			return false;
		};
		listener2->onTouchMoved = [&](Touch* touch, Event* event)
		{
			auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
			_target->setPosition(originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition() - _target->getContentSize() / 2);
		};
		listener2->onTouchEnded = [&](Touch* touch, Event* event)
		{
			_target->GetSprite()->setOpacity(255);

		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, _buildings[1]);
		
}

void MenuLayer::ClearLayer()
{
	_buildings.clear();
	this->removeAllChildren();
}