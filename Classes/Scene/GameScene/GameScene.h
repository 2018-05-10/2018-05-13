/*游戏主要场景类，游戏主体内容在此进行*/

#pragma once
#include "cocos2d.h"

#include"Resource/Mineral.h"
#include"Resource/Power.h"


class ResourceManager;
class SoldierManager;
class MenuLayer;

class MapManager;
class BuildingManager;

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
	BuildingManager* GetEnemyBuildingManager()const;

	//=========获取士兵管理器======
	SoldierManager* GetSoldierManager()const;

	//=========获取游戏内的菜单======
	MenuLayer* GetMenuLayer()const;

	//========获取地图管理器========
	MapManager* GetMapManager()const;

	//===========获取资源类=======
	Mineral* GetMineral();
	Power* GetPower();

	static cocos2d::SpriteFrameCache* _frameCache;

private:
	
	cocos2d::TMXTiledMap* _map;
	MapManager* _mapManager;
	MenuLayer* _menuLayer;
	BuildingManager* _buildingManager;
	BuildingManager* _enemyBuildingManager;
	SoldierManager* _soldierManager;

	Mineral* _mineral;
	Power* _power;
	Mineral* _enemyMineral;
	Power* _enemyPower;

	ResourceManager* _resourceManager;
	
};