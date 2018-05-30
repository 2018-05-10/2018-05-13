/*游戏主要场景类*/

#pragma once
#include "cocos2d.h"
#include"Manager/BuildingManager.h"
#include"Manager/MapManager.h"
#include"MenuLayer.h"


class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	
	cocos2d::TMXTiledMap* GetMap()const;
	BuildingManager* GetBuildingManager()const;
	MenuLayer* GetMenuLayer()const;
	MapManager* GetMapManager()const;
private:
	cocos2d::Sprite *target;
	cocos2d::TMXTiledMap* _map;
	MapManager* _mapManager;
	MenuLayer* _menuLayer;
	BuildingManager* _buildingManager;
	
};