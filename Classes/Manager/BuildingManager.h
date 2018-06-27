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

	

	//=======���콨��ʱ����Դ���=========
	bool BuildingResourceCheck(int name);
	static void ClearAll();

	cocos2d::TMXTiledMap* GetMap();
	SoldierManager* GetSoldierManager();
	MapManager* GetMapManager();
	MenuLayer* GetMenuLayer();
	Mineral* GetMineral();
	Power* GetPower();

	//===========by lym==============
	int GetMineralPerSecond()const;                  //ȡ�õ�ǰ�������������Ŀ󳡵Ĳ������ٶ�
	static void UpdateMineralPerSecond();  
	void UpdateMineral(float dt);
	void BindPower(Power* p);               //��һ����������󣬼���manager�µ����ж���Ӱ��������������
	void BindMineral(Mineral* m);  //��һ����������
	static void DestroyBuilding(Building* B);

	static Building* CreateBuilding(int BuildingTypeName);          //����һ���������󲢰��侫�飬�����ǽ������ֵ��ַ��������硰Mine���ȵ�
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