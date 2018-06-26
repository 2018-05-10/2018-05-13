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
	bool IsWorking();         //����Ƿ���������
	void SetIsWorking(bool a);         //�ı��Ƿ�����״̬
	Sprite* Build(char* TypeName);     //ͨ�����ù�������ĺ�������������ʵ�嵥λ
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

	int _mineralProducePerSecond = 5;    //ÿ���ܲ����Ŀ�������������Mine�����ã�Ϊ�������д��Building��

	cocos2d::Sprite* _timeBar;

	
};