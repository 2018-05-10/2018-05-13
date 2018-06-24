#include "Barrack.h"
#include"Manager\MapManager.h"
#include"Manager\SoldierManager.h"
#include"Scene\GameScene\GameScene.h"
#include"Scene\GameScene\MenuLayer.h"
Barrack::Barrack()
{
	_whatAmI = "Barrack";

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 15;
	_player = 1;
	_buildingID = buildingsID;
	++buildingsID;


}

Barrack::Barrack(Power* p, Mineral* m,int player)
{
	_whatAmI = "Barrack";
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

Barrack::~Barrack()
{
	if (!_player)
	{
		_pPower->Free(_powerCost);
	}
}

bool Barrack::init()
{
	return true;
}

int Barrack::GetPowerCost()
{
	return _powerCost;
}

int Barrack::GetMineralCost()
{
	return _mineralCost;
}

void Barrack::BarrackUpdate(float dt)
{
	if (_buildingList.empty())
	{
		return;
	}
	if (_buildingList.front() == "Infantry")
	{
		auto pos = this->getPosition();
		auto tilePos = MapManager::ChangeToTiledPos(pos);
		auto infantry = SoldierManager::CreateSoldier("Infantry", 0);
		GameScene::GetMap()->addChild(infantry, 150 + tilePos.x + tilePos.y);
		auto landPos = GameScene::GetMapManager()->BFS(pos);
		infantry->setPosition(landPos);
		infantry->schedule(schedule_selector(Soldier::SearchEnemyUpdate), infantry->GetAttackInterval());
		GameScene::GetSoldierManager()->SetSoldierController(infantry);
		GameScene::GetMapManager()->SetSoldier(landPos);
	}
	else if (_buildingList.front() == "Dog")
	{
		auto pos = this->getPosition();
		auto tilePos = MapManager::ChangeToTiledPos(pos);
		auto dog = SoldierManager::CreateSoldier("Dog", 0);
		GameScene::GetMap()->addChild(dog, 150 + tilePos.x + tilePos.y);
		auto landPos = GameScene::GetMapManager()->BFS(pos);
		dog->setPosition(landPos);
		dog->schedule(schedule_selector(Soldier::SearchEnemyUpdate), dog->GetAttackInterval());
		GameScene::GetSoldierManager()->SetSoldierController(dog);
		GameScene::GetMapManager()->SetSoldier(landPos);
	}
	
	_buildingList.pop();
	if (GameScene::GetMenuLayer()->_buildingListUI != nullptr)
	{
		auto lab = static_cast<Text*>(Helper::seekWidgetByName(GameScene::GetMenuLayer()->_buildingListUI, "Number"));
		lab->setText(Value(this->_buildingList.size()).asString());
	}
}