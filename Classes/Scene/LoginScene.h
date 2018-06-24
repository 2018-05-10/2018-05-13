#pragma once
#include"cocos2d.h"
#include"ui\CocosGUI.h"

class LoginScene :public cocos2d::Layer
{
public:

	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(LoginScene);

	void BGinit();
	void createLoginButton();

	void initPlayerBox();

	void menuBackCallback(cocos2d::Ref* pSender);

	void textFieldEvent(cocos2d::Ref* sender, cocos2d::ui::TextField::EventType event);
private:
	cocos2d::ui::TextField* PlayernameInput;
	cocos2d::Sprite* PlayernameBG;
};