#pragma once
#include"cocos2d.h"

#include<list>
#include<queue>

class BuildingManager;
class Mineral;
class MapManager;
class Power;
class Soldier;
class Entity;



class SoldierManager :public cocos2d::Node
{

	//=========by cyy==========
public:
	CREATE_FUNC(SoldierManager);
	virtual bool init();
	void update(float dt);

	bool CheckSoldierResource(char*);

	//=======士兵移动函数==========
	void Move(Soldier*);
	static void EnemyCreate(float x, float y,int type);
	static void SetEnemyTarget(float x,float y,int ID);
	static void SetEnemyTargetEnemy(int, int);
	static void EnemyDie(int ID);

	//======存储被选中士兵的vector
	static std::unordered_map<int ,Soldier*> _beChoosedMap;

	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	MapManager* GetMapManager();
	Mineral* GetMineral();
	Power* GetPower();

	//===========by lym===============
public:
	static std::unordered_map<int,Soldier*> _soldierMap;
	static std::unordered_map<int,Soldier*> _enemySoldierMap;
private:
	static Mineral* _pMineral;
	int _player;
	BuildingManager* _pPairManager;
public:
	static Soldier *CreateSoldier(int SoldierTypeName,int player);
	static Soldier *CreateEnemySoldier(int SoldierTypeName, int player);

	void BindMineral(Mineral* m);
	void DestroySoldier(Soldier* S);
	static void ClearAll();
	void SetPlayer(int num);
	int GetPlayer();
	void SetPairManager(BuildingManager* Pair);
	BuildingManager* GetPairManager();
};