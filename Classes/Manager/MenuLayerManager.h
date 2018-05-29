#pragma once
#include"cocos2d.h"
#include"Scene/MenuLayer.h"

class MenuLayerManager:public cocos2d::Node
{
public:
	CREATE_FUNC(MenuLayerManager);
	virtual bool init();

	void SetBuildingController(cocos2d::Sprite*,cocos2d::Scene*);

	MenuLayer* getMenuLayer() const;
private:
	MenuLayer * _menuLayer;
};