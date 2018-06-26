#pragma once
#include"cocos2d.h"
#include<vector>
#include<string>
class Building;
class BuildingManager;
class SoldierManager;
class Power;
class Mineral;
class Soldier;

class MapManager :public cocos2d::Node
{
	friend class SoldierManager;
public:
	CREATE_FUNC(MapManager);
	virtual bool init();

	//==========tiledmap坐标与cocos坐标互相转换============
	static cocos2d::Vec2 ChangeToTiledPos(cocos2d::Point);
	static cocos2d::Vec2 ChangeToCocosPos(cocos2d::Vec2);

	//========对建筑建造位置的检查==========
	static bool BuildingPositionCheck(cocos2d::Point,int);

	//=======获取tledmap中的瓦片信息，将其存入一个二维vector数组中======
	void GetTiledInformation();

	//=========建筑与士兵建造时，更新地图vector上的信息，建筑占的点设为0，士兵设为2=======
	static void SetBuilding(cocos2d::Point,int);
	static void RemoveBuilding(Building*,int);
	static void RemoveSoldier(Soldier*);
	void SetSoldier(cocos2d::Point);
	static void SoldierDoMove(cocos2d::Point, cocos2d::Point);



	//=======BFS宽度搜索，用于寻找出兵点与多个士兵的目的地=========
	cocos2d::Point BFS(cocos2d::Point);
	void TargetPosBFS(cocos2d::Point);

	//======检测该点是否可通行======
	static bool CheckPos(cocos2d::Point);
	static bool CheckTargetPos(cocos2d::Point);

	//=====获取父节点中的其他子节点的信息======
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	Mineral* GetMineral();
	Power* GetPower();

	//用于存储信息
	static std::vector<std::vector<int>> _mapVec;
	static std::vector<std::vector<int>>_objectVec;

private:

};