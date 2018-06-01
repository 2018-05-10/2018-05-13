#pragma once
#include"cocos2d.h"

class SoldierManager :public cocos2d::Node
{
public:
	CREATE_FUNC(SoldierManager);
	virtual bool init();

	void SetSelectBoxController();

private:
	cocos2d::Point _getTouchBeganPos;
	cocos2d::Point _getTouchEndedPos;
	cocos2d::Sprite* _selectBox;
};