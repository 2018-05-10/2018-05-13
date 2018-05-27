/*开始时菜单界面*/

#pragma once
#include"cocos2d.h"
#include"extensions/cocos-ext.h"
class MenuScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MenuScene);

	void BGinit();

	cocos2d::extension::ControlButton* CreateButton(std::string,int);

	void CreateMusicButton();
	void MenuMusicCallBack(cocos2d::Ref* pSender);

	void TouchQuit(Ref* pSender, cocos2d::extension::Control::EventType event);
	void TouchSetting(Ref* pSender, cocos2d::extension::Control::EventType event);

private:
	bool _musicOn = true;
};
