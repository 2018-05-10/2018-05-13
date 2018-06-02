#pragma once
/*建议先创建两个资源类对象，
再创建建筑管理和士兵管理类，分别绑定到两个资源对象上,将他们互相绑定为Pair Manager。
最后通过管理类创建各种实体*/

#pragma once
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
using namespace cocos2d;

//Resources

/*矿产是一个简单直接的类，暴力的理解为金钱即可*/
class Mineral :public Node
{
public:
	Mineral();
	~Mineral();
	CREATE_FUNC(Mineral);
	bool init();
	int GetCurrentVal();
	void Cost(int val);        //消耗矿产
	void Add(int val);         //增加矿产
private:
	int _currentVal;       //当前量
};

/*电力的机制如下：
分为总量，占用量以及剩余量
总量取决于有多少个电厂，类似于杯子的容量
占有量取决于有多少正在用电动建筑，相当于杯子中已经装的水
剩余量为总量减去占有量，即杯子还能装多少*/
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
	void Use(int val);          //向杯子里面倒水
	void Free(int val);          //将杯子里的水倒出来
	void Add(int val);           //增加总容量
	void Reduce(int val);        //减少总容量
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
	void Hit(int attack);  //被攻击时调用，在Soldier类的Attack函数里被调用
	bool Isdead();  //判断是否死亡
	Size VisualField;    //视野
	char* WhatAmI();
	virtual void Die();    //死亡，调用管理类的函数，再调用析构函数；在子类里定义
private:
	int _player;       //属于哪一方
protected:
	Sprite * _sprite;
	int _totalHP;
	int _currentHP;
	char* _whatAmI;     //类名
};


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
	virtual void Die();
protected:
	bool _isWorking;

	int _powerCost;
	int _mineralCost;

	int _timeToBuild;

	BuildingManager* _pManager = NULL;
	Power* _pPower = NULL;

	int _mineralProducePerSecond = 5;    //每秒能产生的矿物数量，仅在Mine中有用，为方便管理写在Building里
};

class Soldier :public Entity
{
	friend class SoldierManager;
public:
	Soldier();
	virtual ~Soldier();
	int GetAttack();            //获取攻击力数值
	void Attack(Entity* target);           //普通攻击，会先分辨敌我，再攻击
	void ForcedAttack(Entity* target);            //强制攻击，所谓反补
	bool init();
	virtual void Die();
	int _numInVec;             //在管理类里的总序号
	int _numInTypeVec;         //在自己同类当中的序号
protected:
	int _attack;
	int _speed;
	int _mineralCost;
	float _attackInterval;

	SoldierManager* _pSoldierManager;
};


//Managers
/*建筑管理，主要是用来建造，摧毁建筑，以及实现建筑状态与电力和矿产两种资源的配合
所有对象储存在Vector中，建筑对象在Vector里的位置等于该对象本身的序号参数_numInVec*/

class BuildingManager :public Node
{
public:
	CREATE_FUNC(BuildingManager);
	bool init();
	void SetPlayer(int num);                //设定是哪一方
	int GetPlayer();

	Sprite* CreateBuilding(char* BuildingTypeName);          //创建一个建筑对象并绑定其精灵，参数是建筑名字的字符串，例如“Mine”等等
	void DestroyBuilding(Building* B);              //当建筑HP为零时，摧毁建筑，参数是指向该建筑的指针
	int GetMineralPerSecond();                  //取得当前所有正常工作的矿场的产矿总速度
	void UpdateMineralPerSecond();              //建筑或摧毁矿场时更新产矿总速度
	void BindPower(Power* p);               //绑定一个电力类对象，即改manager下的所有对象都影响这个电力类对象
	void BindMineral(Mineral* m);           //绑定一个矿产类对象
	void ClearAll();                        //清除改管理类下的所有对象，在游戏结束的时候调用，防止内存溢出

	void SetPairManager(SoldierManager* Pair);    //绑定属于同一个玩家的士兵管理器
	SoldierManager* GetPairManager();
private:
	Vector<Building*> _buildingVec;
	Power* _pPower = NULL;
	Mineral* _pMineral = NULL;
	int _mineralPerSecond = 0;
	int _player;                   //表示是哪一方的，同一个玩家，即同一方的两个管理类的_side的值相等，且不与其他玩家相等

	SoldierManager* _pPairManager;        //属于同一个玩家的士兵管理器
};

/*Soldier管理类下主要的不同在于除了一个大的Vector存储所有对象，还有三个小Vector来储存三个同类对象*/

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
	Barrack(Power* p, Mineral* m, BuildingManager* pManagerItBelongsTo);       //传入的三个变量分别是为了修改相应的电力，矿产，以及确定该对象在哪个管理类的管理之下
	~Barrack();
	bool init();
	int GetPowerCost();     //所消耗的电力
	int GetMineralCost();       //所消耗的矿物
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
	int GetMineralProducePerSecond();    //每秒产出的矿物数量
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
	const int _powerProduce = 50;     //能提供的电力
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





