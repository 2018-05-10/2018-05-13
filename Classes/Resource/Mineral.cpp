#include "Mineral.h"
#include"Scene/GameScene/GameScene.h"
Mineral::Mineral()
{

}
Mineral::~Mineral(){}

bool Mineral::init()
{
	_currentVal = 2000;
	return true;
}

int Mineral::GetCurrentVal()
{
	return _currentVal;
}

void Mineral::Cost(int val)
{
	_currentVal -= val;
}

void Mineral::Add(int val)
{
	_currentVal += val;
}
