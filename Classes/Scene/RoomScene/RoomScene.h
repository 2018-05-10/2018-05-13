#pragma once
#include"cocos2d.h"
#include"ui\CocosGUI.h"
class RoomScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(RoomScene);

	cocos2d::ui::Button* CreateButton(std::string);
	virtual void update(float dt);

	void CreateMasterLayer();

	void BGinit();
};