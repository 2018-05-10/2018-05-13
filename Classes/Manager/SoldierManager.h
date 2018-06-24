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

	//======单击选择士兵与框选士兵======
	void SetSelectBoxController();
	void SetSoldierController(Soldier*);

	//======为士兵设置目的地=========
	void SetTargetController();
	void SetEnemyTargetController(Entity*);
	bool CheckSoldierResource(char*);

	//=====简单寻路算法=====
	void Square(Soldier*);
	



	

	//=======士兵移动函数==========
	void Move(Soldier*);

	//======存储被选中士兵的vector
	static std::unordered_map<int ,Soldier*> _beChoosedMap;

	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	MapManager* GetMapManager();
	Mineral* GetMineral();
	Power* GetPower();

private:

	
	cocos2d::Point _getTouchBeganPos;
	cocos2d::Point _getTouchEndedPos;

	cocos2d::Sprite* _selectBox;
	

	//===========by lym===============
public:
	static std::unordered_map<int,Soldier*> _soldierMap;
	static std::vector<Soldier*> _dogVec;
	static std::vector<Soldier*> _infantryVec;
	static std::vector<Soldier*> _tankVec;
	static std::unordered_map<int,Soldier*> _enemySoldierMap;
	static std::queue<Soldier*> _searchList;
private:
	static Mineral* _pMineral;
	int _player;
	std::unordered_map<int,Soldier*>::iterator _iter;
	BuildingManager* _pPairManager;
public:
	static Soldier *CreateSoldier(char* SoldierTypeName,int player);
	static Soldier *CreateEnemySoldier(char* SoldierTypeName, int player);

	void BindMineral(Mineral* m);
	void DestroySoldier(Soldier* S);
	void ClearAll();
	void SetPlayer(int num);
	int GetPlayer();
	void SetPairManager(BuildingManager* Pair);
	BuildingManager* GetPairManager();
};