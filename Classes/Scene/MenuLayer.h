#pragma once
#include"cocos2d.h"
#include<vector>
class MenuLayer :public cocos2d::Layer
{
public:

	virtual bool init();
	CREATE_FUNC(MenuLayer);

	cocos2d::Layer* CreateMainLayer();
	cocos2d::Layer* CreateBasementLayer();

	void SetBuildingController(std::vector<cocos2d::Sprite*>);

	
	std::vector<cocos2d::Sprite*> _buildings = {};
private:
	
	cocos2d::Sprite* target;

};