#pragma once
#include "Classes/Entity/Entity.h"
#include "Classes/Resource/Power.h"
#include "Classes/Resource/Mineral.h"

USING_NS_CC;
class BuildingManager;

class Building :public Entity
{
	friend class BuildingManager;
public:
	Building();
	virtual ~Building();
	bool IsWorking();         //检查是否正常工作
	void SetIsWorking(bool a);         //改变是否工作的状态
	Sprite* Build(char* TypeName);     //通过调用管理类里的函数来建造其他实体单位
	bool init();
	int _numInVec;       //在管理类里的Vector的位置，及序号
	//virtual void Die();
	void BuildingUpdate(float dt);
	//=======building id by cyy=======
	int GetBuildingID();
	static int buildingsID;

protected:
	bool _isWorking;



	int _powerCost;
	int _mineralCost;

	int _timeToBuild;

	BuildingManager* _pManager = NULL;
	Power* _pPower = NULL;
	Mineral* _pMineral = NULL;

	int _mineralProducePerSecond = 5;    //每秒能产生的矿物数量，仅在Mine中有用，为方便管理写在Building里


	
};