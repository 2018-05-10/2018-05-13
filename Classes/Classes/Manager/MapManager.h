#pragma once
#include"cocos2d.h"
class MapManager :public cocos2d::Node
{
public:
	CREATE_FUNC(MapManager);
	virtual bool init();

	void MouseMoveEvent(cocos2d::EventMouse  *event);

	void KeyPressedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);
	void KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);

	void SetMouseController();
	void SetKeyboardController();

	void KeyUpdate(float dt);

private:
	cocos2d::TMXTiledMap *_map;
	cocos2d::Point _mapScrScrollSpeed = cocos2d::Point(0, 0);
};