#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Entity :public Node
{
public:
	Entity();
	~Entity();
	Sprite* GetSprite();
	int GetTotalHP();
	int GetCurrentHP();
	void BindSprite(Sprite* sprite);
	void Hit(int attack);
	bool Isdead();
	Size VisualField;
protected:
	Sprite * _sprite;
	int _totalHP;
	int _currentHP;
};