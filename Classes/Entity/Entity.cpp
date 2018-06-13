#include "Entity.h"
using namespace ui;
using namespace cocostudio;

Entity::Entity()
{
	_sprite = NULL;
}
Entity::~Entity()
{
}
Sprite* Entity::GetSprite()
{
	return this->_sprite;
}
void Entity::BindSprite(Sprite* sprite)
{
	this->_sprite = sprite;
	this->addChild(_sprite);

	Size size = _sprite->getContentSize();
	_sprite->setPosition(Point(size.width/2,size.height/2));
	this->setContentSize(size);
	this->setAnchorPoint(Point(0.5,0.5));
}
int Entity::GetTotalHP()
{
	return _totalHP;
}
int Entity::GetCurrentHP()
{
	return _currentHP;
}
void Entity::Hit(int attack)
{
	if (GetSprite() == NULL)
	{
		return;
	}

	_currentHP -= attack;
	float percent = static_cast<float>(_currentHP) / static_cast<float>(_totalHP);
	static_cast<LoadingBar*>(Helper::seekWidgetByName(_hpUI, "HPBar"))->setPercent(percent*100);
	if (_currentHP < 0)
	{
		_currentHP = 0;
	}
	if (_currentHP == 0)
	{
		Die();
	}
}
bool Entity::Isdead()
{
	if (_currentHP == 0)
	{
		return true;
	}
	return false;
}
char* Entity::WhatAmI()
{
	return _whatAmI;
}
void Entity::Die()
{}

void Entity::SetPlayer(int num)
{
	_player = num;
}
int Entity::GetPlayer()
{
	return _player;
}