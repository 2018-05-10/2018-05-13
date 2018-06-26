/*��Ϸ��Ҫ�����࣬��Ϸ���������ڴ˽���*/

#pragma once
#include "cocos2d.h"

#include"Resource/Mineral.h"
#include"Resource/Power.h"


class ResourceManager;
class SoldierManager;
class MenuLayer;
class GameController;
class MapManager;
class BuildingManager;

class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	//========������ʼ��=====
	virtual bool init();
	//virtual void onEnter();

	CREATE_FUNC(GameScene);

	void RecvDataUpdate(float dt);
	void initBattle();

	//======��ȡ��ͼ========
	static cocos2d::TMXTiledMap* GetMap();

	//======��ȡ����������========
	static BuildingManager* GetBuildingManager();

	//=========��ȡʿ��������======
	static SoldierManager* GetSoldierManager();

	//=========��ȡ��Ϸ�ڵĲ˵�======
	static MenuLayer* GetMenuLayer();

	//========��ȡ��ͼ������========
	static MapManager* GetMapManager();

	static GameController* GetGameController();

	//===========��ȡ��Դ��=======
	static Mineral* GetMineral();
	static Power* GetPower();

	static cocos2d::SpriteFrameCache* _frameCache;

private:
	
	static cocos2d::TMXTiledMap* _map;
	static MapManager* _mapManager;
	static MenuLayer* _menuLayer;
	static BuildingManager* _buildingManager;
	static SoldierManager* _soldierManager;
	static GameController* _gameController;
	static Mineral* _mineral;
	static Power* _power;


	
};