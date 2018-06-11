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
	
	//=======每秒增加矿产========
	void UpdateMineral(float dt);
	
	//=====获取父节点中的其他子节点的信息======
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	Mineral* GetMineral();
	Power* GetPower();
};