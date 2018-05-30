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
	void CreateContructionLayer();
	void CreateSoldierLayer();
	void ClearLayer();

	void SetBuildingListController();
	void SetBaseConstructionController();
	void SetBarrackConstructionController();
	void SetMineConstructionController();
	void SetPowerStationController();
	
private:

	Building* _target;
	std::vector<cocos2d::Sprite*> _buildings = {};
};