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

	//=====��ê���Ϊ��ͼƬ����======
	void BindSprite(Sprite* sprite);
	void Hit(int attack);  //������ʱ���ã���Soldier���Attack�����ﱻ����
	bool Isdead();  //�ж��Ƿ�����
	Size VisualField;    //��Ұ
	int Type();
	virtual void Die();    //���������ù�����ĺ������ٵ��������������������ﶨ��
	int GetID();
	
protected:
	Sprite * _sprite;
	int _totalHP;
	int _currentHP;
	int _type;     //����
	int _player;       //������һ��
	int _ID;
	cocos2d::Sprite* _hpBar;
	bool _isDead=false;
};