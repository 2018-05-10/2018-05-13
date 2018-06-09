#pragma once
#include"cocos2d.h"
#include"Entity/Soldier/Soldier.h"

class BuildingManager;
class Mineral;
class MapManager;
class Power;

class SoldierManager :public cocos2d::Node
{

	//=========by cyy==========
public:
	CREATE_FUNC(SoldierManager);
	virtual bool init();

	//======单击选择士兵与框选士兵======
	void SetSelectBoxController();
	void SetSoldierController(Soldier*);

	//======为士兵设置目的地=========
	void SetTargetController();
	bool CheckSoldierResource(char*);

	//=====简单寻路算法=====
	void Square(Soldier*);

	//======检测该点是否可通行======
	bool CheckPos(Point);

	//=======士兵移动函数==========
	void Move(Soldier*);

	//======存储被选中士兵的vector
	static cocos2d::Vector<Soldier*> _beChoosed;

	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	MapManager* GetMapManager();
	Mineral* GetMineral();
	Power* GetPower();

private:

	
	cocos2d::Point _getTouchBeganPos;
	cocos2d::Point _getTouchEndedPos;
	static  cocos2d::Vector<Soldier*> _enemySoldierVec;

	cocos2d::Sprite* _selectBox;
	

	//===========by lym===============
private:
	static cocos2d::Vector<Soldier*> _soldierVec;
	static cocos2d::Vector<Soldier*> _dogVec;
	static cocos2d::Vector<Soldier*> _infantryVec;
	static cocos2d::Vector<Soldier*> _tankVec;
	Mineral* _pMineral;
	int _player;

	BuildingManager* _pPairManager;
public:
	Soldier *CreateSoldier(char* SoldierTypeName,int player);

	void BindMineral(Mineral* m);
	void DestroySoldier(Soldier* S);
	void ClearAll();
	void SetPlayer(int num);
	int GetPlayer();
	void SetPairManager(BuildingManager* Pair);
	BuildingManager* GetPairManager();
};