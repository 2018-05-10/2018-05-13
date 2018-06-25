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

	//==========tiledmap������cocos���껥��ת��============
	static cocos2d::Vec2 ChangeToTiledPos(cocos2d::Point);
	static cocos2d::Vec2 ChangeToCocosPos(cocos2d::Vec2);

	//========�Խ�������λ�õļ��==========
	static bool BuildingPositionCheck(cocos2d::Point,int);

	//=======��ȡtledmap�е���Ƭ��Ϣ���������һ����άvector������======
	void GetTiledInformation();

	//=========������ʿ������ʱ�����µ�ͼvector�ϵ���Ϣ������ռ�ĵ���Ϊ0��ʿ����Ϊ2=======
	static void SetBuilding(cocos2d::Point,int);
	static void RemoveBuilding(Building*,int);
	static void RemoveSoldier(Soldier*);
	void SetSoldier(cocos2d::Point);
	static void SoldierDoMove(cocos2d::Point, cocos2d::Point);



	//=======BFS�������������Ѱ�ҳ���������ʿ����Ŀ�ĵ�=========
	cocos2d::Point BFS(cocos2d::Point);
	void TargetPosBFS(cocos2d::Point);

	//======���õ��Ƿ��ͨ��======
	static bool CheckPos(cocos2d::Point);
	static bool CheckTargetPos(cocos2d::Point);

	//=====��ȡ���ڵ��е������ӽڵ����Ϣ======
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	Mineral* GetMineral();
	Power* GetPower();

	//���ڴ洢��Ϣ
	static std::vector<std::vector<int>> _mapVec;
	static std::vector<std::vector<int>>_objectVec;

private:

};