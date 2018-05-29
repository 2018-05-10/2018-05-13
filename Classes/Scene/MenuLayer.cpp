#include"MenuLayer.h"
#include"Manager/MenuLayerManager.h"
#include"GameScene.h"
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
	
	return true;
}

Layer* MenuLayer::CreateMainLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	menuLayer->setContentSize(Size(visibleSize.width*0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	
	
	return menuLayer;
}
cocos2d::Layer*  MenuLayer::CreateBasementLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	menuLayer->setContentSize(Size(visibleSize.width *0.3, visibleSize.height));
	menuLayer->setOpacity(100);
	

	auto contentSize = menuLayer->getContentSize();

	auto factory =Sprite::create("Building/factory.png");
	factory->setPosition(Point(contentSize.width / 4, contentSize.height * 3 / 4));
	menuLayer->addChild(factory);
	_buildings.push_back(factory);
	
	auto soldier_factory= Sprite::create("Building/soldier_factory.png");
	soldier_factory->setPosition(contentSize.width *3/4, contentSize.height * 3 / 4);
	menuLayer->addChild(soldier_factory);
	_buildings.push_back(soldier_factory);

	
	return menuLayer;
}

void MenuLayer::SetBuildingController(std::vector<Sprite*> buildings)
{
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = [&](Touch *touch, Event *event)
		{

			auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
			Point pos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
			if (target1->getBoundingBox().containsPoint(pos))
			{
				auto visibleSize = Director::getInstance()->getVisibleSize();
				target = Sprite::createWithSpriteFrame(_buildings[0]->getSpriteFrame());
				target->setOpacity(100);
				static_cast<GameScene*>(this->getParent())->GetMap()->addChild(target, 2);
				auto worldPos = Point(_buildings[0]->getPosition().x + visibleSize.width*0.7, _buildings[0]->getPosition().y)
					- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
				target->setPosition(worldPos);

				return true;
			}
			return false;
		};
		listener->onTouchMoved = [&](Touch* touch, Event* event)
		{
			auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
			target->setPosition(originPos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition());
		};
		listener->onTouchEnded = [&](Touch* touch, Event* event)
		{
			target->setOpacity(255);
		};

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), _buildings[0]);
	
		
}