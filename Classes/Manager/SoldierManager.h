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