/*��Ϸ��Ҫ�����࣬��Ϸ���������ڴ˽���*/

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

	//========������ʼ��=====
	virtual bool init();

	CREATE_FUNC(GameScene);

	//======��ȡ��ͼ========
	cocos2d::TMXTiledMap* GetMap();

	//======��ȡ����������========
	BuildingManager* GetBuildingManager()const;

	//=========��ȡʿ��������======
	SoldierManager* GetSoldierManager()const;

	//=========��ȡ��Ϸ�ڵĲ˵�======
	MenuLayer* GetMenuLayer()const;

	//========��ȡ��ͼ������========
	MapManager* GetMapManager()const;

	//===========��ȡ��Դ��=======
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