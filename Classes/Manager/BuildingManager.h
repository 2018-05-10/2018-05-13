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
	


	//========不同建筑的点击事件=====
	void SetBaseController(Building*);
	void SetBarrackController(Building*);
	void SetFactoryController(Building*);
	void SetProducerController(Building*);

	//=======建造建筑时的资源检测=========
	bool BuildingResourceCheck(int name);

	cocos2d::TMXTiledMap* GetMap();
	SoldierManager* GetSoldierManager();
	MapManager* GetMapManager();
	MenuLayer* GetMenuLayer();
	Mineral* GetMineral();
	Power* GetPower();

	//===========by lym==============
	int GetMineralPerSecond()const;                  //取得当前所有正常工作的矿场的产矿总速度
	static void UpdateMineralPerSecond();              //建筑或摧毁矿场时更新产矿总速度  =======进行了一些改动 by cyy========
	void BindPower(Power* p);               //绑定一个电力类对象，即改manager下的所有对象都影响这个电力类对象
	void BindMineral(Mineral* m);  //绑定一个矿产类对象
	void DestroyBuilding(Building* B);

	Building* CreateBuilding(char* BuildingTypeName);          //创建一个建筑对象并绑定其精灵，参数是建筑名字的字符串，例如“Mine”等等
	Building* CreateEnemyBuilding(char* BuildingTypeName);
	static std::vector<Building*>  _buildingVec;
	static std::vector<Building*> _enemyBuildingVec;
	static int _mineralPerSecond;
private:

	Power * _pPower = NULL;
	Mineral* _pMineral = NULL;


};