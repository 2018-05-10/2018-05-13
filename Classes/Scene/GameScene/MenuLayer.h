#pragma once
#include"cocos2d.h"
#include"Entity/Building/Building.h"
#include<vector>
class MenuLayer :public cocos2d::Layer
{
public:

	virtual bool init();
	CREATE_FUNC(MenuLayer);

	void CreateMainLayer();
	void CreateBaseLayer();
	void ClearLayer();

	void SetBuildingController();

	
	
private:

	Building* _target;
	std::vector<cocos2d::Sprite*> _buildings = {};
};