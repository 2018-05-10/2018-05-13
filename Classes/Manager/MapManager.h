#pragma once
#include"cocos2d.h"
#include<vector>
#include<string>
class BuildingManager;
class SoldierManager;
class Power;
class Mineral;

class MapManager :public cocos2d::Node
{
	friend class SoldierManager;
public:
	CREATE_FUNC(MapManager);
	virtual bool init();

	//==========移动地图视角的函数========
	void KeyPressedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);
	void KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);

	void SetMouseController();
	void SetKeyboardController();
	void ControllerUpdate(float dt);

	//==========tiledmap坐标与cocos坐标互相转换============
	cocos2d::Vec2 ChangeToTiledPos(cocos2d::Point);
	cocos2d::Vec2 ChangeToCocosPos(cocos2d::Vec2);

	//========对建筑建造位置的检查==========
	bool BuildingPositionCheck(cocos2d::Point,int);

	//=======获取tledmap中的瓦片信息，将其存入一个二维vector数组中======
	void GetTiledInformation();

	//=========建筑与士兵建造时，更新地图vector上的信息，建筑占的点设为0，士兵设为2=======
	void SetBuilding(cocos2d::Point,int);
	void SetSoldier(cocos2d::Point);
	void SoldierDoMove(cocos2d::Point, cocos2d::Point);

	//=========测试时使用的函数========
	void SetTestListener();

	//=======BFS宽度搜索，用于寻找出兵点与多个士兵的目的地=========
	cocos2d::Point BFS(cocos2d::Point);
	void TargetPosBFS(cocos2d::Point);

	//=====获取父节点中的其他子节点的信息======
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	Mineral* GetMineral();
	Power* GetPower();

	//用于存储信息
	std::vector<std::vector<int>> _mapVec;
	std::vector<std::vector<int>>_objectVec;

private:



	bool _isClick = false;
	bool _key_A_isPressed=false;
	bool _key_W_isPressed = false;
	bool _key_D_isPressed = false;
	bool _key_S_isPressed = false;

	//=======鼠标光标位置======
	cocos2d::Point _mousePosition = cocos2d::Point(0, 0);
};