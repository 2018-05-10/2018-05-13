#include "Entity.h"

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
	_sprite->setPosition(Point(size.width / 2, size.height / 2));
	this->setContentSize(size);
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
	if (_currentHP < 0)
	{
		_currentHP = 0;
	}
	if (_currentHP == 0)
	{
		
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
