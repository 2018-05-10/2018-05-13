#pragma once
#include "Classes/Entity/Entity.h"
#include "Classes/Resource/Power.h"
#include "Classes/Resource/Mineral.h"
#include "ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
class BuildingManager;

class Building :public Entity
{
	friend class BuildingManager;
	friend class GameScene;
	friend class NetScene;
public:
	Building();
	virtual ~Building();
	bool IsWorking();         //检查是否正常工作
	void SetIsWorking(bool a);         //改变是否工作的状态
	Sprite* Build(char* TypeName);     //通过调用管理类里的函数来建造其他实体单位
	bool init();
	virtual void Die();
	void BuildingUpdate(float dt);
	void update(float dt);



protected:
	bool _isWorking;

	static int buildingsID;
	static int enemyBuildingsID;


	int _powerCost;
	int _mineralCost;

	int _timeToBuild;

	BuildingManager* _pManager = NULL;
	Power* _pPower = NULL;
	Mineral* _pMineral = NULL;

	int _mineralProducePerSecond = 5;    //每秒能产生的矿物数量，仅在Mine中有用，为方便管理写在Building里

	cocos2d::Sprite* _timeBar;

	
};