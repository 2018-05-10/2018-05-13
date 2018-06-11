/*��Ϸ�ڵĲ˵���������ʿ���Ľ����ڴ˽���*/

#pragma once
#include"cocos2d.h"

#include<vector>

class  MapManager;
class  BuildingManager;
class  SoldierManager;
class  Building;

class MenuLayer :public cocos2d::Layer
{
public:

	virtual bool init();
	CREATE_FUNC(MenuLayer);

	//=====��ʼ�����˵�=====
	void CreateMainLayer();

	//======��ʼ����������˵�=====
	void CreateContructionLayer();

	//========��ʼ��ʿ������˵�====
	void CreateSoldierLayer(int);

	//========��ʼ��ս������˵�=====
	void CreateFactoryLayer(int);

	//=======�����ǰ�˵������л��˵�ʱ����======
	void ClearLayer();

	//=======��ʼ�������˵���˵�еĲ˵����ڻ����˵��Ļ����ϴ���======
	cocos2d::Layer* CreateLayer();

	//========���ֿ��ؼ�����ú���=========
	void CreateMusicButton();
	void MenuMusicCallBack(cocos2d::Ref* pSender);

	//=========�Խ������찴ť�ļ�غ���========
	void SetBuildingListController();
	void SetBaseConstructionController();
	void SetBarrackConstructionController( );
	void SetMineConstructionController();
	void SetPowerStationController();
	void SetFactoryController();

	//=====��ȡ���ڵ��е������ӽڵ����Ϣ======
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	MapManager* GetMapManager();
	
	
private:
	std::vector<cocos2d::Sprite*> _buildings;
	cocos2d::Sprite* _target;
	bool _musicOn = true;
};