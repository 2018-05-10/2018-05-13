#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
USING_NS_CC;

//Entities
class Entity :public Node
{
	friend class GameController;
public:
	Entity();
	virtual ~Entity();
	void SetPlayer(int num);
	int GetPlayer();
	int GetType();

	Sprite* GetSprite();
	int GetTotalHP();
	int GetCurrentHP();

	//=====将锚点改为了图片中央======
	void BindSprite(Sprite* sprite);
	void Hit(int attack);  //被攻击时调用，在Soldier类的Attack函数里被调用
	bool Isdead();  //判断是否死亡
	Size VisualField;    //视野
	int Type();
	virtual void Die();    //死亡，调用管理类的函数，再调用析构函数；在子类里定义
	int GetID();
	
protected:
	Sprite * _sprite;
	int _totalHP;
	int _currentHP;
	int _type;     //类名
	int _player;       //属于哪一方
	int _ID;
	cocos2d::Sprite* _hpBar;
	bool _isDead=false;
};