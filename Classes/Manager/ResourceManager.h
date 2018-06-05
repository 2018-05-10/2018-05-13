#pragma once
#include"cocos2d.h"
class BuildingManager;
class SoldierManager;
class Mineral;
class Power;

class ResourceManager :public cocos2d::Node 
{
public:
	CREATE_FUNC(ResourceManager);
	void UpdateMineral(float dt);//每秒增加矿产
	
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	Mineral* GetMineral();
	Power* GetPower();
};