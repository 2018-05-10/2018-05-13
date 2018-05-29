#pragma once
#include"cocos2d.h"
#include"Scene/GameScene.h"
#include"Manager/MapManager.h"
class MapController :public cocos2d::Node
{
public:
	CREATE_FUNC(MapController);

	void SetMouseController(MapManager*);
	void SeyKeyboardController(MapManager*);
};
