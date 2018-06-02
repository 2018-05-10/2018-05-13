#pragma once
#include"cocos2d.h"
#include"extensions/cocos-ext.h"
#include"ui/CocosGUI.h"

class SettingScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);

	void BGinit();

	cocos2d::ui::Button* CreateButton(std::string, int);

	void CreateMusicButton();
	void MenuMusicCallBack(cocos2d::Ref* pSender);

	void CreateSlider();
	void SliderCallBack(Ref *pSender, cocos2d::ui::Slider::EventType type);

private:
	bool _musicOn = true;
};