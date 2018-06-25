#pragma once
#include"cocos2d.h"

class Soldier;
class Entity;
class Building;

class GameController :public cocos2d::Node
{
public:

	CREATE_FUNC(GameController);
	virtual bool init();

	void KeyPressedEvent(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
	void KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
	void SetMouseController();
	void SetKeyboardController();

	//======单击选择士兵与框选士兵======
	void SetSelectBoxController();
	void SetSoldierController(Soldier*);

	//======为士兵设置目的地=========
	void SetTargetController();
	void SetEnemyTargetController(Entity*);
	void ControllerUpdate(float dt);

	//========建筑的点击事件=====
	void SetBuildingController(Building*);

private:

	bool _isClick = false;
	bool _key_A_isPressed = false;
	bool _key_W_isPressed = false;
	bool _key_D_isPressed = false;
	bool _key_S_isPressed = false;

	cocos2d::Point _getTouchBeganPos;
	cocos2d::Point _getTouchEndedPos;

	cocos2d::Sprite* _selectBox;


	cocos2d::Point _mousePosition = cocos2d::Point(800, 450);
};