#include "Building.h"
#include"Manager/BuildingManager.h"
#include"Scene/GameScene/GameScene.h"
#include"PowerStation.h"

Building::Building() {}

Building::~Building() {}

bool Building::IsWorking()
{
	return _isWorking;
}

void Building::SetIsWorking(bool a)
{
	_isWorking = a;
}

//Sprite* Building::Build(char* TypeName)
//{
//	Sprite* a = NULL;
//	a = _pManager->CreateBuilding(TypeName);
//	if (a == NULL)
//	{
//		a = _pManager->GetPairManager()->CreateSoldier(TypeName);
//	}
//	return a;
//}

bool Building::init()
{
	return true;
}

//void Building::Die()
//{
//	_pManager->DestroyBuilding(this);
//}



//========building ID by cyy=====
int Building::buildingsID = 2;

int Building::GetBuildingID()
{
	return buildingsID;
}

void Building::BuildingUpdate(float dt)
{
	
	if (_pPower->GetUsedVal() > _pPower->GetTotalVal())
	{
		
		_isWorking = false;
	}
	else
	{
		GetSprite()->setColor(Color3B(255, 255, 255));
		_isWorking = true;

		int freePower = _pPower->GetAvailableVal();
		if (_whatAmI == "Mine")
		{
			BuildingManager::UpdateMineralPerSecond();
		}
		if (_whatAmI == "PowerStation")
		{
			if (freePower > 0)
			{
				_pPower->Add(static_cast<PowerStation*>(this)->GetPowerProduce());
				Building* p = NULL;
				for (int i = 0; i <BuildingManager::_buildingVec.size(); i++)
				{
					p = BuildingManager::_buildingVec.at(i);
					if ((!p->_isWorking) && (p->_powerCost <= freePower))
					{
						freePower -= p->_powerCost;
						p->_isWorking = true;
						_pPower->Use(p->_powerCost);
					}
				}
			}
		}
		
	}
	
}