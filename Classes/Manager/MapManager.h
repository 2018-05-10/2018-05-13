#pragma once
#include"cocos2d.h"
#include"Scene/GameScene/GameScene.h"

class MapManager :public cocos2d::Node
{
public:
	CREATE_FUNC(MapManager);
	virtual bool init();


	void KeyPressedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);
	void KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);

	void SetMouseController();
	void SetKeyboardController();

	void ControllerUpdate(float dt);

private:
	cocos2d::Point _mapScrScrollSpeed = cocos2d::Point(0, 0);

	bool _isClick = false;
	bool _key_A_isPressed=false;
	bool _key_W_isPressed = false;
	bool _key_D_isPressed = false;
	bool _key_S_isPressed = false;

	cocos2d::Point _mousePosition = cocos2d::Point(0, 0);
};