#pragma once
#include"cocos2d.h"
#include"Entity/Building/Building.h"

class SoldierManager;
class MapManager;
class Mineral;
class Power;
class MenuLayer;

class BuildingManager :public cocos2d::Node
{
	
public:
	CREATE_FUNC(BuildingManager);
	
	virtual bool init();

	

	//=======建造建筑时的资源检测=========
	bool BuildingResourceCheck(int name);
	static void ClearAll();

	cocos2d::TMXTiledMap* GetMap();
	SoldierManager* GetSoldierManager();
	MapManager* GetMapManager();
	MenuLayer* GetMenuLayer();
	Mineral* GetMineral();
	Power* GetPower();

	//===========by lym==============
	int GetMineralPerSecond()const;                  //取得当前所有正常工作的矿场的产矿总速度
	static void UpdateMineralPerSecond();  
	void UpdateMineral(float dt);
	void BindPower(Power* p);               //绑定一个电力类对象，即改manager下的所有对象都影响这个电力类对象
	void BindMineral(Mineral* m);  //绑定一个矿产类对象
	static void DestroyBuilding(Building* B);

	static Building* CreateBuilding(int BuildingTypeName);          //创建一个建筑对象并绑定其精灵，参数是建筑名字的字符串，例如“Mine”等等
	static Building* CreateEnemyBuilding(int BuildingTypeName);
	static std::unordered_map<int,Building*>  _buildingMap;
	static std::unordered_map<int,Building*> _enemyBuildingMap;

	static int _mineralPerSecond;
private:
	static Power* _pPower;
	static Mineral* _pMineral;
	static int _myBuildingCount;
	static int _opBuildingCount;
};