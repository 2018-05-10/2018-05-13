#pragma once
#include"cocos2d.h"
#include"ui/CocosGUI.h"
#include"extensions/cocos-ext.h"

class LoadingScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadingScene);

	void LoadSound();
	void LoadImage();
	void endLoading();
	void LoadSpriteFrame();
	cocos2d::ui::LoadingBar* createLoadingBar();
};