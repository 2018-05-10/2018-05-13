/*游戏主要场景类，游戏主体内容在此进行*/

#pragma once
#include "cocos2d.h"
#include"Manager/BuildingManager.h"
#include"Manager/MapManager.h"
#include"MenuLayer.h"
#include"Manager/SoldierManager.h"
#include"Resource/Mineral.h"
#include"Resource/Power.h"

class ResourceManager;

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	//========场景初始化=====
	virtual bool init();

	CREATE_FUNC(GameScene);

	//======获取地图========
	cocos2d::TMXTiledMap* GetMap();

	//======获取建筑管理器========
	BuildingManager* GetBuildingManager()const;

	//=========获取士兵管理器======
	SoldierManager* GetSoldierManager()const;

	//=========获取游戏内的菜单======
	MenuLayer* GetMenuLayer()const;

	//========获取地图管理器========
	MapManager* GetMapManager()const;

	//===========获取资源类=======
	Mineral* GetMineral();
	Power* GetPower();

private:
	
	cocos2d::TMXTiledMap* _map;
	MapManager* _mapManager;
	MenuLayer* _menuLayer;
	BuildingManager* _buildingManager;
	SoldierManager* _soldierManager;
	Mineral* _mineral;
	Power* _power;
	ResourceManager* _resourceManager;
	
};