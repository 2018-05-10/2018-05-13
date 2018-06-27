#pragma once
#include"cocos2d.h"

class ResultScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ResultScene);

	virtual void update(float dt);

	void BGinit();
};