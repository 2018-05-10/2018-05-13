/*��Ϸ�ڵĲ˵���������ʿ���Ľ����ڴ˽���*/

#pragma once
#include"cocos2d.h"
#include<vector>
#include"ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"

using namespace cocos2d::ui;
using namespace cocostudio;

class  MapManager;
class  BuildingManager;
class  SoldierManager;
class  Building;
class Mineral;
class Power;

class MenuLayer :public cocos2d::Layer
{
	friend class Factory;
	friend class Barrack;
public:

	virtual bool init();
	CREATE_FUNC(MenuLayer);

	void update(float dt);
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
	cocos2d::Menu* CreateMusicButton();
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
	Mineral* GetMineral();
	Power* GetPower();
	
private:
	std::vector<cocos2d::Sprite*> _buildings;
	cocos2d::Sprite* _target;
	cocos2d::Layer* _layer;
	bool _musicOn = true;
	Widget* _resourceUI;
	Widget* _buildingListUI;
};