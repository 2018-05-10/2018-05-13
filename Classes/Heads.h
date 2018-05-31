#pragma once
/*�����ȴ���������Դ�����
�ٴ������������ʿ�������࣬�ֱ�󶨵�������Դ������,�����ǻ����ΪPair Manager��
���ͨ�������ഴ������ʵ��*/

#pragma once
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
using namespace cocos2d;

//Resources

/*�����һ����ֱ�ӵ��࣬���������Ϊ��Ǯ����*/
class Mineral :public Node
{
public:
	Mineral();
	~Mineral();
	CREATE_FUNC(Mineral);
	bool init();
	int GetCurrentVal();
	void Cost(int val);        //���Ŀ��
	void Add(int val);         //���ӿ��
private:
	int _currentVal;       //��ǰ��
};

/*�����Ļ������£�
��Ϊ������ռ�����Լ�ʣ����
����ȡ�����ж��ٸ��糧�������ڱ��ӵ�����
ռ����ȡ�����ж��������õ綯�������൱�ڱ������Ѿ�װ��ˮ
ʣ����Ϊ������ȥռ�����������ӻ���װ����*/
class Power :public Node
{
public:
	Power();
	~Power();
	CREATE_FUNC(Power);
	bool init();

	int GetTotalVal();
	int GetUsedVal();
	int GetAvailableVal();
	void Use(int val);          //�������浹ˮ
	void Free(int val);          //���������ˮ������
	void Add(int val);           //����������
	void Reduce(int val);        //����������
private:
	int _totalVal;
	int _usedVal;
	int _availableVal;
};



//Entities
class Entity :public Node
{
public:
	Entity();
	virtual ~Entity();
	void SetPlayer(int num);
	int GetPlayer();

	Sprite* GetSprite();
	int GetTotalHP();
	int GetCurrentHP();
	void BindSprite(Sprite* sprite);
	void Hit(int attack);  //������ʱ���ã���Soldier���Attack�����ﱻ����
	bool Isdead();  //�ж��Ƿ�����
	Size VisualField;    //��Ұ
	char* WhatAmI();
	virtual void Die();    //���������ù�����ĺ������ٵ��������������������ﶨ��
private:
	int _player;       //������һ��
protected:
	Sprite * _sprite;
	int _totalHP;
	int _currentHP;
	char* _whatAmI;     //����
};


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
	virtual void Die();
protected:
	bool _isWorking;

	int _powerCost;
	int _mineralCost;

	int _timeToBuild;

	BuildingManager* _pManager = NULL;
	Power* _pPower = NULL;

	int _mineralProducePerSecond = 5;    //ÿ���ܲ����Ŀ�������������Mine�����ã�Ϊ�������д��Building��
};

class Soldier :public Entity
{
	friend class SoldierManager;
public:
	Soldier();
	virtual ~Soldier();
	int GetAttack();            //��ȡ��������ֵ
	void Attack(Entity* target);           //��ͨ���������ȷֱ���ң��ٹ���
	void ForcedAttack(Entity* target);            //ǿ�ƹ�������ν����
	bool init();
	virtual void Die();
	int _numInVec;             //�ڹ�������������
	int _numInTypeVec;         //���Լ�ͬ�൱�е����
protected:
	int _attack;
	int _speed;
	int _mineralCost;
	float _attackInterval;

	SoldierManager* _pSoldierManager;
};


//Managers
/*����������Ҫ���������죬�ݻٽ������Լ�ʵ�ֽ���״̬������Ϳ��������Դ�����
���ж��󴢴���Vector�У�����������Vector���λ�õ��ڸö��������Ų���_numInVec*/

class BuildingManager :public Node
{
public:
	CREATE_FUNC(BuildingManager);
	bool init();
	void SetPlayer(int num);                //�趨����һ��
	int GetPlayer();

	Sprite* CreateBuilding(char* BuildingTypeName);          //����һ���������󲢰��侫�飬�����ǽ������ֵ��ַ��������硰Mine���ȵ�
	void DestroyBuilding(Building* B);              //������HPΪ��ʱ���ݻٽ�����������ָ��ý�����ָ��
	int GetMineralPerSecond();                  //ȡ�õ�ǰ�������������Ŀ󳡵Ĳ������ٶ�
	void UpdateMineralPerSecond();              //������ݻٿ�ʱ���²������ٶ�
	void BindPower(Power* p);               //��һ����������󣬼���manager�µ����ж���Ӱ��������������
	void BindMineral(Mineral* m);           //��һ����������
	void ClearAll();                        //����Ĺ������µ����ж�������Ϸ������ʱ����ã���ֹ�ڴ����

	void SetPairManager(SoldierManager* Pair);    //������ͬһ����ҵ�ʿ��������
	SoldierManager* GetPairManager();
private:
	Vector<Building*> _buildingVec;
	Power* _pPower = NULL;
	Mineral* _pMineral = NULL;
	int _mineralPerSecond = 0;
	int _player;                   //��ʾ����һ���ģ�ͬһ����ң���ͬһ���������������_side��ֵ��ȣ��Ҳ�������������

	SoldierManager* _pPairManager;        //����ͬһ����ҵ�ʿ��������
};

/*Soldier����������Ҫ�Ĳ�ͬ���ڳ���һ�����Vector�洢���ж��󣬻�������СVector����������ͬ�����*/

class SoldierManager :public Node
{
public:
	CREATE_FUNC(SoldierManager);
	bool init();
	void SetPlayer(int num);
	int GetPlayer();

	void BindMineral(Mineral* m);
	Sprite* CreateSoldier(char* SoldierTypeName);
	void DestroySoldier(Soldier* S);
	void ClearAll();

	void SetPairManager(BuildingManager* Pair);
	BuildingManager* GetPairManager();
private:
	Vector<Soldier*> _soldierVec;
	Vector<Soldier*> _dogVec;
	Vector<Soldier*> _infantryVec;
	Vector<Soldier*> _tankVec;
	Mineral* _pMineral;
	int _player;

	BuildingManager* _pPairManager;
};


//Building
class Base :public Building
{
public:
	Base();
	Base(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);
	~Base();
	bool init();
	int GetPowerCost();
};

class Barrack :public Building
{
public:
	Barrack();
	Barrack(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);       //��������������ֱ���Ϊ���޸���Ӧ�ĵ�����������Լ�ȷ���ö������ĸ�������Ĺ���֮��
	~Barrack();
	bool init();
	int GetPowerCost();     //�����ĵĵ���
	int GetMineralCost();       //�����ĵĿ���
private:
};

class Factory :public Building
{
public:
	Factory();
	Factory(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);
	~Factory();
	bool init();
	int GetPowerCost();
	int GetMineralCost();
private:
};

class Mine :public Building
{
public:
	Mine();
	Mine(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);
	~Mine();
	int GetMineralCost();
	int GetPowerCost();
	int GetMineralProducePerSecond();    //ÿ������Ŀ�������
	bool init();

};

class PowerStation :public Building
{
public:
	PowerStation();
	PowerStation(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);
	~PowerStation();
	bool init();
	int GetPowerProduce();
	int GetMineralCost();
private:
	const int _powerProduce = 50;     //���ṩ�ĵ���
};


//Soldier
class Tank :public Soldier
{
public:
	Tank();
	Tank(Mineral* m, SoldierManager* p);
	~Tank();
	bool init();
private:

};

class Dog :public Soldier
{
public:
	Dog();
	Dog(Mineral* m, SoldierManager* p);
	~Dog();
	bool init();
private:
};

class Infantry :public Soldier
{
public:
	Infantry();
	Infantry(Mineral *m, SoldierManager* p);
	~Infantry();
	bool init();
private:
};





