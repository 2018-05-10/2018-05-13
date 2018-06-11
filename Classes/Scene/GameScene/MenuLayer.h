/*游戏内的菜单，建筑，士兵的建造在此进行*/

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

	//=====初始化主菜单=====
	void CreateMainLayer();

	//======初始化建筑建造菜单=====
	void CreateContructionLayer();

	//========初始化士兵建造菜单====
	void CreateSoldierLayer(int);

	//========初始化战场建造菜单=====
	void CreateFactoryLayer(int);

	//=======清除当前菜单，在切换菜单时调用======
	void ClearLayer();

	//=======初始化基础菜单，说有的菜单都在基础菜单的基础上创建======
	cocos2d::Layer* CreateLayer();

	//========音乐开关及其调用函数=========
	void CreateMusicButton();
	void MenuMusicCallBack(cocos2d::Ref* pSender);

	//=========对建筑建造按钮的监控函数========
	void SetBuildingListController();
	void SetBaseConstructionController();
	void SetBarrackConstructionController( );
	void SetMineConstructionController();
	void SetPowerStationController();
	void SetFactoryController();

	//=====获取父节点中的其他子节点的信息======
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	MapManager* GetMapManager();
	
	
private:
	std::vector<cocos2d::Sprite*> _buildings;
	cocos2d::Sprite* _target;
	bool _musicOn = true;
};