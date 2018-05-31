#include "Heads.h"

bool BuildingManager::init()
{
	this->scheduleUpdate();
	return true;
}

void BuildingManager::BindPower(Power* p)
{
	_pPower = p;
}

void BuildingManager::BindMineral(Mineral* m)
{
	_pMineral = m;
}

void BuildingManager::UpdateMineralPerSecond()
{
	int val = 0;
	Building* p = NULL;
	for (int i = 0; i < _buildingVec.size(); i++)
	{
		p = _buildingVec.at(i);
		if ((p->_whatAmI == "Mine") && (p->_isWorking))
		{
			val += p->_mineralProducePerSecond;
		}
	}
	_mineralPerSecond = val;
}

Sprite* BuildingManager::CreateBuilding(char* BuildingTypeName)
{
	Building* B = NULL;
	Sprite* spr = NULL;
	if (BuildingTypeName == "Base")
	{
		B = new Base(_pPower, _pMineral, this);
		spr = Sprite::create("Base.png");
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Barrack")
	{
		B = new Barrack(_pPower, _pMineral, this);
		spr = Sprite::create("Barrack.png");
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "Mine")
	{
		B = new Mine(_pPower, _pMineral, this);
		spr = Sprite::create("Mine.png");
		B->BindSprite(spr);
	}
	else if (BuildingTypeName == "PowerStation")
	{
		B = new PowerStation(_pPower, _pMineral, this);
		spr = Sprite::create("PowerStation.png");
		B->BindSprite(spr);
	}
	else
	{
		return NULL;
	}
	_buildingVec.pushBack(B);
	B->_numInVec = _buildingVec.size() - 1;
	int freePower = _pPower->GetAvailableVal();
	if (B->_whatAmI == "PowerStation")
	{
		if (freePower > 0)
		{
			Building* p = NULL;
			for (int i = 0; i < _buildingVec.size(); i++)
			{
				p = _buildingVec.at(i);
				if ((!p->_isWorking) && (p->_powerCost <= freePower))
				{
					freePower -= p->_powerCost;
					p->_isWorking = true;
					_pPower->Use(p->_powerCost);
				}
			}
		}
	}
	if (B->_whatAmI == "Mine")
	{
		UpdateMineralPerSecond();
	}

	return spr;
}

void BuildingManager::DestroyBuilding(Building* B)
{
	int i = B->_numInVec;
	_buildingVec.replace(i, NULL);
	if (B->_whatAmI == "PowerStation")
	{
		int freePower = _pPower->GetAvailableVal();
		while (true)
		{
			int i = _buildingVec.size() - 1;
			if (freePower < 0)
			{
				Building* p = _buildingVec.at(i);
				if (p != NULL)
				{
					p->_isWorking = false;
					freePower + p->_powerCost;
				}
				--i;
			}
			else
			{
				break;
			}
		}
	}
	if (B->_whatAmI == "Mine")
	{
		UpdateMineralPerSecond();
	}
	delete B;
}

int BuildingManager::GetMineralPerSecond()
{
	return _mineralPerSecond;
}

void BuildingManager::ClearAll()
{
	Building* p = NULL;
	for (int i = 0; i < _buildingVec.size(); i++)
	{
		p = _buildingVec.at(i);
		if (p != NULL)
		{
			delete p;
		}
	}
}

void BuildingManager::SetPlayer(int num)
{
	_player = num;
}

int BuildingManager::GetPlayer()
{
	return _player;
}

void BuildingManager::SetPairManager(SoldierManager* pair)
{
	_pPairManager = pair;
}

SoldierManager* BuildingManager::GetPairManager()
{
	return _pPairManager;
}