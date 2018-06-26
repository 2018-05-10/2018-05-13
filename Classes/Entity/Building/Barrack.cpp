#include "Barrack.h"
#include"Manager\MapManager.h"
#include"Manager\SoldierManager.h"
#include"Scene\GameScene\GameScene.h"
#include"Scene\GameScene\MenuLayer.h"
#include"Controller/GameController.h"
#include"Entity/Player.h"

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

Barrack::Barrack()
{
	_type = BARRACK;

	_totalHP = 2000;
	_currentHP = 2000;
	_powerCost = 35;
	_mineralCost = 100;
	_timeToBuild = 15;
	_player = 1;
	_ID = enemyBuildingsID;
	++enemyBuildingsID;


}

Barrack::Barrack(Power* p, Mineral* m,int player)
{
	_type = BARRACK;
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
		auto infantry = SoldierManager::CreateSoldier(INFANTRY, 0);
		GameScene::GetMap()->addChild(infantry, 150 + tilePos.x + tilePos.y);
		auto landPos = GameScene::GetMapManager()->BFS(pos);
		infantry->setPosition(landPos);
		Player::getInstance()->client->SendData(landPos.x, landPos.y, 0, infantry->GetID(), INFANTRY, CREATE_ENEMY);
		infantry->schedule(schedule_selector(Soldier::SearchEnemyUpdate), infantry->GetAttackInterval());
		GameScene::GetGameController()->SetSoldierController(infantry);
		GameScene::GetMapManager()->SetSoldier(landPos);
	}
	else if (_buildingList.front() == "Dog")
	{
		auto pos = this->getPosition();
		auto tilePos = MapManager::ChangeToTiledPos(pos);
		auto dog = SoldierManager::CreateSoldier(DOG, 0);
		GameScene::GetMap()->addChild(dog, 150 + tilePos.x + tilePos.y);
		auto landPos = GameScene::GetMapManager()->BFS(pos);
		dog->setPosition(landPos);
		Player::getInstance()->client->SendData(landPos.x, landPos.y, 0, dog->GetID(), DOG, CREATE_ENEMY);
		dog->schedule(schedule_selector(Soldier::SearchEnemyUpdate), dog->GetAttackInterval());
		GameScene::GetGameController()->SetSoldierController(dog);
		GameScene::GetMapManager()->SetSoldier(landPos);
	}
	
	_buildingList.pop();
	if (GameScene::GetMenuLayer()->_buildingListUI != nullptr)
	{
		auto lab = static_cast<Text*>(Helper::seekWidgetByName(GameScene::GetMenuLayer()->_buildingListUI, "Number"));
		lab->setText(Value(this->_buildingList.size()).asString());
	}
}