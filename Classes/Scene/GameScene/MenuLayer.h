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
	void CreateSoldierLayer(int);
	void CreateFactoryLayer(int);
	void ClearLayer();
	cocos2d::Layer* CreateLayer();

	void CreateMusicButton();
	void MenuMusicCallBack(cocos2d::Ref* pSender);

	void SetBuildingListController();
	void SetBaseConstructionController();
	void SetBarrackConstructionController( );
	void SetMineConstructionController();
	void SetPowerStationController();
	void SetFactoryController();
	
private:
	std::vector<cocos2d::Sprite*> _buildings;
	Building* _target;
	bool _musicOn = true;
};