#include"GameScene.h"
#include"MenuLayer.h"
#include"Entity/Building/Base.h"
#include"Entity\Soldier\Soldier.h"
#include"Manager/BuildingManager.h"
#include"Manager/MapManager.h"
#include"MenuLayer.h"
#include"Manager/SoldierManager.h"
#include"Setting.h"
#include"Controller\GameController.h"
#include"Entity\Soldier\Soldier.h"
#include"Net\API.h"
#include"Entity\Player.h"
#include"Scene/RoomScene/ChatBox.h"
#include"Scene/ResultScene.h"

USING_NS_CC;
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
#define ENEMY_DIE 1003

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin= Director::getInstance()->getVisibleOrigin();

	_map = TMXTiledMap::create("Map/map1.tmx");
	this->addChild(_map,0);
	_map->setPosition(-1875,-937.5);
	 _mapManager = MapManager::create();
	this->addChild(_mapManager,1);

	_buildingManager = BuildingManager::create();
	this->addChild(_buildingManager, 1);

	_gameController = GameController::create();
	this->addChild(_gameController, 1);

	_menuLayer = MenuLayer::create();
	this->addChild(_menuLayer, 10);
	_soldierManager = SoldierManager::create();
	this->addChild(_soldierManager, 1);


	_power = Power::create();
	_mineral = Mineral::create();
	this->addChild(_power, 1);
	this->addChild(_mineral, 1);
	_buildingManager->BindMineral(_mineral);
	_buildingManager->BindPower(_power);
	_soldierManager->BindMineral(_mineral);



	_gameController->SetMouseController();
	_gameController->SetKeyboardController();
	_gameController->schedule(schedule_selector(GameController::ControllerUpdate));
	_mapManager->GetTiledInformation();

	_gameController->SetSelectBoxController();
	_gameController->SetTargetController();


	_mineral->schedule(schedule_selector(BuildingManager::UpdateMineral), 1.0f);

	auto layer = LayerColor::create(Color4B::WHITE);
	layer->setOpacity(150);
	layer->setContentSize(Size(visibleSize.width / 6, visibleSize.height/5));
	this->addChild(layer);
	auto chatBox = ChatBox::create();
	chatBox->setPosition(visibleSize.width * 0.08f, visibleSize.height * 0.15f);
	layer->addChild(chatBox);

	initBattle();


	this->schedule(schedule_selector(GameScene::RecvDataUpdate));
	
	return true;
}

void onEnter()
{

}

void GameScene::RecvDataUpdate(float dt)
{
	while (!Player::getInstance()->client->_orders.empty())
	{
		switch (Player::getInstance()->client->_orders.front()._func)
		{
		case CREATE_ENEMY:
				SoldierManager::EnemyCreate(Player::getInstance()->client->_orders.front()._x, 
				Player::getInstance()->client->_orders.front()._y, 
				Player::getInstance()->client->_orders.front()._kind,
				Player::getInstance()->client->_orders.front()._id);
				break;
		case SET_ENEMY_TARGET:
				SoldierManager::SetEnemyTarget(Player::getInstance()->client->_orders.front()._x, 
				Player::getInstance()->client->_orders.front()._y,
				Player::getInstance()->client->_orders.front()._id);
				break;
		case SET_ENEMY_TARGET_ENEMY:
				SoldierManager::SetEnemyTargetEnemy(Player::getInstance()->client->_orders.front()._id,
				Player::getInstance()->client->_orders.front()._goal);
				break;
		case ENEMY_DIE:
				SoldierManager::EnemyDie(Player::getInstance()->client->_orders.front()._id);
				break;
		}
		Player::getInstance()->client->_orders.pop_front();
	}
	if (Player::getInstance()->quitGame)
	{
		auto transition = TransitionFade::create(0.3, ResultScene::createScene());
		Director::getInstance()->replaceScene(transition);
	}
}

void GameScene::initBattle()
{
	if (Player::getInstance()->isMaster)
	{
		auto base = BuildingManager::CreateBuilding(BASE);
		_map->addChild(base, 0);
		base->setPosition(MapManager::ChangeToCocosPos(Point(60, 5)));
		GetMapManager()->SetBuilding(MapManager::ChangeToCocosPos(Point(60,5)), BASE);
		base->scheduleOnce(schedule_selector(Building::BuildingUpdate), 0.1);
		_gameController->SetBuildingController(base);
		Player::getInstance()->client->SendData(MapManager::ChangeToCocosPos(Point(60, 5)).x, MapManager::ChangeToCocosPos(Point(60, 5)).y, 0, base->GetID(), base->GetType(), CREATE_ENEMY);
	}
	else
	{
		auto base = BuildingManager::CreateBuilding(BASE);
		_map->addChild(base, 0);
		base->setPosition(MapManager::ChangeToCocosPos(Point(5, 60)));
		GetMapManager()->SetBuilding(MapManager::ChangeToCocosPos(Point(5,60)), BASE);
		base->scheduleOnce(schedule_selector(Building::BuildingUpdate), 0.1);
		_gameController->SetBuildingController(base);
		Player::getInstance()->client->SendData(MapManager::ChangeToCocosPos(Point(5,60)).x, MapManager::ChangeToCocosPos(Point(5,60)).y, 0, base->GetID(), base->GetType(), CREATE_ENEMY);
	}
}

void GameScene::onExit()
{

	SoldierManager::ClearAll();
	BuildingManager::ClearAll();
	MapManager::ClearAll();
	Player::getInstance()->isEnd += 10000;
	if (Player::getInstance()->isMaster)
	{
		if (Player::getInstance()->getResult())
		{
			Player::getInstance()->client->_chatMsgSend.push_back("is_ended_master");
		}
		else
		{
			Player::getInstance()->client->_chatMsgSend.push_back("is_ended_client");
		}
	
	}
	Layer::onExit();
}


TMXTiledMap* GameScene::GetMap()
{
	return _map;
}
BuildingManager*  GameScene::GetBuildingManager()
{
	return _buildingManager;
}
MenuLayer* GameScene::GetMenuLayer()
{
	return _menuLayer;
}
MapManager* GameScene::GetMapManager()
{
	return _mapManager;
}
SoldierManager* GameScene::GetSoldierManager()
{
	return _soldierManager;
}
Mineral* GameScene::GetMineral()
{
	return _mineral;
}
Power* GameScene::GetPower()
{
	return _power;
}
GameController* GameScene::GetGameController()
{
	return _gameController;
}

SpriteFrameCache* GameScene::_frameCache = SpriteFrameCache::getInstance();
TMXTiledMap* GameScene::_map;
MapManager* GameScene::_mapManager;
MenuLayer* GameScene::_menuLayer;
BuildingManager* GameScene::_buildingManager;
SoldierManager* GameScene::_soldierManager;
Mineral* GameScene::_mineral;
Power* GameScene::_power;
GameController* GameScene::_gameController;