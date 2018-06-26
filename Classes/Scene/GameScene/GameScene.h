/*游戏主要场景类，游戏主体内容在此进行*/

#pragma once
#include "cocos2d.h"

#include"Resource/Mineral.h"
#include"Resource/Power.h"


class ResourceManager;
class SoldierManager;
class MenuLayer;
class GameController;
class MapManager;
class BuildingManager;

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	//========场景初始化=====
	virtual bool init();
	//virtual void onEnter();

	CREATE_FUNC(GameScene);

	void RecvDataUpdate(float dt);
	void initBattle();

	//======获取地图========
	static cocos2d::TMXTiledMap* GetMap();

	//======获取建筑管理器========
	static BuildingManager* GetBuildingManager();

	//=========获取士兵管理器======
	static SoldierManager* GetSoldierManager();

	//=========获取游戏内的菜单======
	static MenuLayer* GetMenuLayer();

	//========获取地图管理器========
	static MapManager* GetMapManager();

	static GameController* GetGameController();

	//===========获取资源类=======
	static Mineral* GetMineral();
	static Power* GetPower();

	static cocos2d::SpriteFrameCache* _frameCache;

private:
	
	static cocos2d::TMXTiledMap* _map;
	static MapManager* _mapManager;
	static MenuLayer* _menuLayer;
	static BuildingManager* _buildingManager;
	static SoldierManager* _soldierManager;
	static GameController* _gameController;
	static Mineral* _mineral;
	static Power* _power;


	
};