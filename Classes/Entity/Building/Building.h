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
	bool IsWorking();         //����Ƿ���������
	void SetIsWorking(bool a);         //�ı��Ƿ�����״̬
	Sprite* Build(char* TypeName);     //ͨ�����ù�������ĺ�������������ʵ�嵥λ
	bool init();
	int _numInVec;       //�ڹ��������Vector��λ�ã������
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

	int _mineralProducePerSecond = 5;    //ÿ���ܲ����Ŀ�������������Mine�����ã�Ϊ�������д��Building��


	
};