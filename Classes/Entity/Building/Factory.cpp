#include "Factory.h"
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
#include"Manager\MapManager.h"
#include"Manager\SoldierManager.h"
#include"Scene\GameScene\GameScene.h"
#include"Scene\GameScene\MenuLayer.h"
#include"Entity\Soldier\Soldier.h"

Factory::Factory()
{
	_whatAmI = "Factory";
	
	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 1;
	_player = 1;
	_buildingID = buildingsID;
	++buildingsID;

	
}

Factory::Factory(Power* p, Mineral* m,int player)
{
	_whatAmI = "Factory";
	_pPower = p;


	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 1;
	_player = player;
	_buildingID = buildingsID;
	++buildingsID;

	m->Cost(_mineralCost);
	p->Use(_powerCost);
	_isWorking = false;
}

Factory::~Factory()
{
	if (!_player)
	{
		_pPower->Free(_powerCost);
	}
}

bool Factory::init()
{
	return true;
}

int Factory::GetPowerCost()
{
	return _powerCost;
}

int Factory::GetMineralCost()
{
	return _mineralCost;
}

void Factory::FactoryUpdate(float dt)
{
	if (_buildingList.empty())
	{
		return;
	}
	if (_buildingList.front() == "Tank")
	{
		auto pos =this->getPosition();
		auto tilePos = MapManager::ChangeToTiledPos(pos);
		auto tank = SoldierManager::CreateSoldier("Tank", 0);
		GameScene::GetMap()->addChild(tank, 150 + tilePos.x + tilePos.y);
		auto landPos = GameScene::GetMapManager()->BFS(pos);
		tank->setPosition(landPos);
		tank->schedule(schedule_selector(Soldier::SearchEnemyUpdate), tank->GetAttackInterval());
		GameScene::GetSoldierManager()->SetSoldierController(tank);
		GameScene::GetMapManager()->SetSoldier(landPos);
		_buildingList.pop();
		if (GameScene::GetMenuLayer()->_buildingListUI!=nullptr)
		{
			auto lab = static_cast<Text*>(Helper::seekWidgetByName(GameScene::GetMenuLayer()->_buildingListUI, "Number"));
			lab->setText(Value(this->_buildingList.size()).asString());
		}
		
	}
}