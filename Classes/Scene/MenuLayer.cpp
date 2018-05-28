#include"MenuLayer.h"

USING_NS_CC;

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto _menuLayer=CreateLayer();
	this->addChild(_menuLayer);

	return true;
}

Layer* MenuLayer::CreateLayer()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto _menuLayer = LayerColor::create(Color4B(0, 128, 128, 255));
	_menuLayer->setContentSize(Size(visibleSize.width / 4, visibleSize.height));
	_menuLayer->setOpacity(100);

	return _menuLayer;
}