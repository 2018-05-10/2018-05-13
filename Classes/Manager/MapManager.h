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

	//==========�ƶ���ͼ�ӽǵĺ���========
	void KeyPressedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);
	void KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code,cocos2d::Event *event);

	void SetMouseController();
	void SetKeyboardController();
	void ControllerUpdate(float dt);

	//==========tiledmap������cocos���껥��ת��============
	cocos2d::Vec2 ChangeToTiledPos(cocos2d::Point);
	cocos2d::Vec2 ChangeToCocosPos(cocos2d::Vec2);

	//========�Խ�������λ�õļ��==========
	bool BuildingPositionCheck(cocos2d::Point,int);

	//=======��ȡtledmap�е���Ƭ��Ϣ���������һ����άvector������======
	void GetTiledInformation();

	//=========������ʿ������ʱ�����µ�ͼvector�ϵ���Ϣ������ռ�ĵ���Ϊ0��ʿ����Ϊ2=======
	void SetBuilding(cocos2d::Point,int);
	void SetSoldier(cocos2d::Point);
	void SoldierDoMove(cocos2d::Point, cocos2d::Point);

	//=========����ʱʹ�õĺ���========
	void SetTestListener();

	//=======BFS�������������Ѱ�ҳ���������ʿ����Ŀ�ĵ�=========
	cocos2d::Point BFS(cocos2d::Point);
	void TargetPosBFS(cocos2d::Point);

	//=====��ȡ���ڵ��е������ӽڵ����Ϣ======
	cocos2d::TMXTiledMap* GetMap();
	BuildingManager* GetBuildingManager();
	SoldierManager* GetSoldierManager();
	Mineral* GetMineral();
	Power* GetPower();

	//���ڴ洢��Ϣ
	std::vector<std::vector<int>> _mapVec;
	std::vector<std::vector<int>>_objectVec;

private:



	bool _isClick = false;
	bool _key_A_isPressed=false;
	bool _key_W_isPressed = false;
	bool _key_D_isPressed = false;
	bool _key_S_isPressed = false;

	//=======�����λ��======
	cocos2d::Point _mousePosition = cocos2d::Point(0, 0);
};