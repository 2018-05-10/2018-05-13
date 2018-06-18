#pragma once
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
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

	//=====��ê���Ϊ��ͼƬ����======
	void BindSprite(Sprite* sprite);
	void Hit(int attack);  //������ʱ���ã���Soldier���Attack�����ﱻ����
	bool Isdead();  //�ж��Ƿ�����
	Size VisualField;    //��Ұ
	char* WhatAmI();
	virtual void Die();    //���������ù�����ĺ������ٵ��������������������ﶨ��

	
protected:
	Sprite * _sprite;
	int _totalHP;
	int _currentHP;
	char* _whatAmI;     //����
	int _player;       //������һ��
	cocos2d::Sprite* _hpBar;
};