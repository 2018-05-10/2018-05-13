#pragma once
#include"cocos2d.h"
#include"extensions/cocos-ext.h"


class NetScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(NetScene);

	void BGinit();
	cocos2d::ui::Button* CreateButton(std::string, int);
};