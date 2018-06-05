#pragma once
#include"cocos2d.h"
#include"Entity/Building/Building.h"
#include<vector>

class  MapManager;
class  BuildingManager;
class  SoldierManager;

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

	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	MapManager* GetMapManager();
	
	
private:
	std::vector<cocos2d::Sprite*> _buildings;
	cocos2d::Sprite* _target;
	bool _musicOn = true;
};