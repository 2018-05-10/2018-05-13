#pragma once
#include"cocos2d.h"

class MenuLayer :public cocos2d::Layer
{
public:

	virtual bool init();
	CREATE_FUNC(MenuLayer);

	cocos2d::Layer* CreateLayer();

private:
	
};