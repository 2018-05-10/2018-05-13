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

	void SetSelectBoxController();
	void SetSoldierController(Soldier*);
	void SetTargetController();
	bool CheckSoldierResource(char*);
	void MoveUpdate(float dt);
	void Square(Soldier*);
	bool CheckNextPos(Point);

	static cocos2d::Vector<Soldier*> _beChoosed;

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
private:
	static cocos2d::Vector<Soldier*> _soldierVec;
	static cocos2d::Vector<Soldier*> _dogVec;
	static cocos2d::Vector<Soldier*> _infantryVec;
	static cocos2d::Vector<Soldier*> _tankVec;
	Mineral* _pMineral;
	int _player;

	BuildingManager* _pPairManager;
public:
	Soldier *CreateSoldier(char* SoldierTypeName);

	void BindMineral(Mineral* m);
	void DestroySoldier(Soldier* S);
	void ClearAll();
	void SetPlayer(int num);
	int GetPlayer();
	void SetPairManager(BuildingManager* Pair);
	BuildingManager* GetPairManager();
};