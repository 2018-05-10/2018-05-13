#pragma once
#include"cocos2d.h"
#include<vector>
#include<string>
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

	cocos2d::Vec2 ChangeToTiledPos(cocos2d::Point);
	cocos2d::Vec2 ChangeToCocosPos(cocos2d::Vec2);

	bool BuildingCheck(cocos2d::Point,int);
	void GetTiledInformation();
	void SetBuilding(cocos2d::Point,int);
	void SetSoldier(cocos2d::Point);


	void SetTestListener();

	cocos2d::Point BFS(cocos2d::Point);
private:
	std::vector<std::vector<int>> _mapVec;


	bool _isClick = false;
	bool _key_A_isPressed=false;
	bool _key_W_isPressed = false;
	bool _key_D_isPressed = false;
	bool _key_S_isPressed = false;

	cocos2d::Point _mousePosition = cocos2d::Point(0, 0);
};