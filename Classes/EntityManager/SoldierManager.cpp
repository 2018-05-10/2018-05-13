#include "Heads.h"

bool SoldierManager::init()
{
	return true;
}

void SoldierManager::BindMineral(Mineral* m)
{
	_pMineral = m;
}

Sprite* SoldierManager::CreateSoldier(char* SoldierNameType)
{
	Sprite* spr = NULL;
	Soldier* S = NULL;
	if (SoldierNameType == "Dog")
	{
		S = new Dog(_pMineral, this);
		_dogVec.pushBack(S);
		S->_numInTypeVec = _dogVec.size() - 1;
		spr = Sprite::create("Dog.png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Infantry")
	{
		S = new Infantry(_pMineral, this);
		_infantryVec.pushBack(S);
		S->_numInTypeVec = _infantryVec.size() - 1;
		spr = Sprite::create("Infantry.png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Tank")
	{
		S = new Tank(_pMineral, this);
		_tankVec.pushBack(S);
		S->_numInTypeVec = _tankVec.size() - 1;
		spr = Sprite::create("Tank.png");
		S->BindSprite(spr);
	}
	else
	{
		return NULL;
	}

	_soldierVec.pushBack(S);
	S->_numInVec = _soldierVec.size() - 1;

	return spr;
}

void SoldierManager::DestroySoldier(Soldier* S)
{
	if (S->_whatAmI == "Dog")
	{
		_dogVec.replace(S->_numInTypeVec, NULL);
	}
	else if (S->_whatAmI == "Infantry")
	{
		_infantryVec.replace(S->_numInTypeVec, NULL);
	}
	else if (S->_whatAmI == "Tank")
	{
		_tankVec.replace(S->_numInTypeVec, NULL);
	}

	_soldierVec.replace(S->_numInVec, NULL);

	delete S;
}

void SoldierManager::ClearAll()
{
	Soldier* S = NULL;
	for (int i = 0; i < _soldierVec.size(); i++)
	{
		S = _soldierVec.at(i);
		if (S != NULL)
		{
			delete S;
		}
	}
}

void SoldierManager::SetPlayer(int num)
{
	_player = num;
}

int SoldierManager::GetPlayer()
{
	return _player;
}

void SoldierManager::SetPairManager(BuildingManager* Pair)
{
	_pPairManager = Pair;
}

BuildingManager* SoldierManager::GetPairManager()
{
	return _pPairManager;
}