#pragma once
#include "cocos2d.h"
USING_NS_CC;

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

	//=====将锚点改为了图片中央======
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