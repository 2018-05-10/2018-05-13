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
	


	//========��ͬ�����ĵ���¼�=====
	void SetBaseController(Building*);
	void SetBarrackController(Building*);
	void SetFactoryController(Building*);
	void SetProducerController(Building*);

	//=======���콨��ʱ����Դ���=========
	bool BuildingResourceCheck(int name);

	cocos2d::TMXTiledMap* GetMap();
	SoldierManager* GetSoldierManager();
	MapManager* GetMapManager();
	MenuLayer* GetMenuLayer();
	Mineral* GetMineral();
	Power* GetPower();

	//===========by lym==============
	int GetMineralPerSecond()const;                  //ȡ�õ�ǰ�������������Ŀ󳡵Ĳ������ٶ�
	void UpdateMineralPerSecond();              //������ݻٿ�ʱ���²������ٶ�  =======������һЩ�Ķ� by cyy========
	void BindPower(Power* p);               //��һ����������󣬼���manager�µ����ж���Ӱ��������������
	void BindMineral(Mineral* m);           //��һ����������

	Building* CreateBuilding(char* BuildingTypeName);          //����һ���������󲢰��侫�飬�����ǽ������ֵ��ַ��������硰Mine���ȵ�
private:
	Vector<Building*> _buildingVec;
	Power * _pPower = NULL;
	Mineral* _pMineral = NULL;
	int _mineralPerSecond = 0;
	int _player;
};