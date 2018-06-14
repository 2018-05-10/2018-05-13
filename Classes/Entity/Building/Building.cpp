#include "Building.h"
#include"Manager/BuildingManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Manager/MapManager.h"
#include"PowerStation.h"

Building::Building() 
{

}

Building::~Building() {}

bool Building::IsWorking()
{
	return _isWorking;
}

void Building::SetIsWorking(bool a)
{
	_isWorking = a;
}



bool Building::init()
{
	return true;
}

void Building::Die()
{

	GameScene::GetMapManager()->RemoveBuilding(this, _whatAmI);
	GameScene::GetBuildingManager()->DestroyBuilding(this);
}



//========building ID by cyy=====
int Building::buildingsID = 2;

int Building::GetBuildingID()
{
	return _buildingID;
}

void Building::BuildingUpdate(float dt)
{
	if (_hpUI != nullptr&&!_player)
	{
		this->unscheduleUpdate();
		auto timrBar = Helper::seekWidgetByName(_hpUI, "buildingTimeBar");
		timrBar->removeFromParent();
	}
	if (_player)
	{
		GetSprite()->setColor(Color3B(255, 255, 255));
		return;
	}
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

void Building::update(float dt)
{
	auto timeBar = static_cast<LoadingBar*>(Helper::seekWidgetByName(_hpUI, "buildingTimeBar"));
	timeBar->setPercent(timeBar->getPercent()+100.0f/(static_cast<float>(_timeToBuild)*60));
}