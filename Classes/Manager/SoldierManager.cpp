#include"SoldierManager.h"

USING_NS_CC;

bool SoldierManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	
	_selectBox = Sprite::create("selectbox.jpeg");
	this->addChild(_selectBox);
	_selectBox->setOpacity(0);
	return true;
}

void SoldierManager::SetSelectBoxController()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		_getTouchBeganPos = Director::getInstance()->convertToGL(touch->getLocationInView());
		_selectBox->setOpacity(0);
		return true;
	};
	listener->onTouchMoved = [&](Touch *touch, Event *event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_selectBox->setContentSize(Size(abs(originPos.x - _getTouchBeganPos.x), abs(originPos.y - _getTouchBeganPos.y)));
		_selectBox->setPosition(originPos/2+ _getTouchBeganPos/2);
		_selectBox->setOpacity(150);
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event)
	{
		_selectBox->setOpacity(0);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}