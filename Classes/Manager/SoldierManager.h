#pragma once
#include"cocos2d.h"
#include"Entity/Soldier/Soldier.h"
#include<list>

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

	//======����ѡ��ʿ�����ѡʿ��======
	void SetSelectBoxController();
	void SetSoldierController(Soldier*);

	//======Ϊʿ������Ŀ�ĵ�=========
	void SetTargetController();
	void SetEnemyTargetController(Entity*);
	bool CheckSoldierResource(char*);

	//=====��Ѱ·�㷨=====
	void Square(Soldier*);

	

	//=======ʿ���ƶ�����==========
	void Move(Soldier*);

	//======�洢��ѡ��ʿ����vector
	static std::vector<Soldier*> _beChoosed;

	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	MapManager* GetMapManager();
	Mineral* GetMineral();
	Power* GetPower();

private:

	
	cocos2d::Point _getTouchBeganPos;
	cocos2d::Point _getTouchEndedPos;
	static  std::vector<Soldier*> _enemySoldierVec;

	cocos2d::Sprite* _selectBox;
	

	//===========by lym===============
public:
	static std::vector<Soldier*> _soldierVec;
	static std::vector<Soldier*> _dogVec;
	static std::vector<Soldier*> _infantryVec;
	static std::vector<Soldier*> _tankVec;
	static std::vector<Soldier*> _enemySoldier;
private:
	static Mineral* _pMineral;
	int _player;

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