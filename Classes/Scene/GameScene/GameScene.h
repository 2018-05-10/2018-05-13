/*游戏主要场景类*/

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
	virtual bool init();
	CREATE_FUNC(GameScene);

	
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager()const;
	SoldierManager* GetSoldierManager()const;
	MenuLayer* GetMenuLayer()const;
	MapManager* GetMapManager()const;
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