#include "Factory.h"
#include "Building.h"
#include "Resource/Mineral.h"
#include"Resource/Power.h"
#include"Manager\MapManager.h"
#include"Manager\SoldierManager.h"
#include"Scene\GameScene\GameScene.h"
#include"Scene\GameScene\MenuLayer.h"
#include"Entity\Soldier\Soldier.h"
#include"Controller\GameController.h"
#include"Entity\Player.h"

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8
#define CREATE_ENEMY 1000
#define SET_ENEMY_TARGET 1001
#define SET_ENEMY_TARGET_ENEMY 1002


Factory::Factory()
{
	_type = FACTORY;
	
	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 1;
	_player = 1;
	_ID = enemyBuildingsID;
	++enemyBuildingsID;

	
}

Factory::Factory(Power* p, Mineral* m,int player)
{
	_type=FACTORY;
	_pPower = p;


	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 1;
	_player = player;
	_ID = buildingsID;
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
		auto tank = SoldierManager::CreateSoldier(TANK, 0);
		GameScene::GetMap()->addChild(tank, 150 + tilePos.x + tilePos.y);
		auto landPos = GameScene::GetMapManager()->BFS(pos);
		tank->setPosition(landPos);
		Player::getInstance()->client->SendData(landPos.x,landPos.y,0,tank->GetID(),TANK,CREATE_ENEMY);
		tank->schedule(schedule_selector(Soldier::SearchEnemyUpdate), tank->GetAttackInterval());
		GameScene::GetGameController()->SetSoldierController(tank);
		GameScene::GetMapManager()->SetSoldier(landPos);
		_buildingList.pop();
		if (GameScene::GetMenuLayer()->_buildingListUI!=nullptr)
		{
			auto lab = static_cast<Text*>(Helper::seekWidgetByName(GameScene::GetMenuLayer()->_buildingListUI, "Number"));
			lab->setText(Value(this->_buildingList.size()).asString());
		}
		
	}
}