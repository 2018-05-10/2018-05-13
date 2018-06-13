/*��Ϸ��Ҫ�����࣬��Ϸ���������ڴ˽���*/

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

	//========������ʼ��=====
	virtual bool init();

	CREATE_FUNC(GameScene);

	//======��ȡ��ͼ========
	cocos2d::TMXTiledMap* GetMap();

	//======��ȡ����������========
	BuildingManager* GetBuildingManager()const;
	BuildingManager* GetEnemyBuildingManager()const;

	//=========��ȡʿ��������======
	SoldierManager* GetSoldierManager()const;

	//=========��ȡ��Ϸ�ڵĲ˵�======
	MenuLayer* GetMenuLayer()const;

	//========��ȡ��ͼ������========
	MapManager* GetMapManager()const;

	//===========��ȡ��Դ��=======
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