#include"GameScene.h"
#include"MenuLayer.h"
#include"Entity/Building/Base.h"
#include"Manager/ResourceManager.h"
USING_NS_CC;

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

	_map = TMXTiledMap::create("map.tmx");
	this->addChild(_map,0);
	_map->setPosition(-1875,-937.5);
	 _mapManager = MapManager::create();
	this->addChild(_mapManager,1);
	_buildingManager = BuildingManager::create();
	this->addChild(_buildingManager, 1);
	_menuLayer = MenuLayer::create();
	this->addChild(_menuLayer, 10);
	_soldierManager = SoldierManager::create();
	this->addChild(_soldierManager, 1);
	_resourceManager = ResourceManager::create();
	this->addChild(_resourceManager, 1);
	_power = Power::create();
	_mineral = Mineral::create();
	this->addChild(_power, 1);
	this->addChild(_mineral, 1);
	_buildingManager->BindMineral(_mineral);
	_buildingManager->BindPower(_power);
	_soldierManager->BindMineral(_mineral);


	_mapManager->SetMouseController();
	_mapManager->SetKeyboardController();
	_mapManager->schedule(schedule_selector(MapManager::ControllerUpdate));
	_mapManager->SetTestListener();
	_mapManager->GetTiledInformation();

	_soldierManager->SetSelectBoxController();
	_soldierManager->SetTargetController();


	_mineral->schedule(schedule_selector(ResourceManager::UpdateMineral), 1.0f);

	auto base = _buildingManager->CreateBuilding("Base");
	_map->addChild(base,0);
	base->setPosition(2000,1000);
	GetMapManager()->SetBuilding(Point(2000,1000),0);
	base->scheduleOnce(schedule_selector(Building::BuildingUpdate), 0);
	_buildingManager->SetBaseController(base);
	

	return true;
}

TMXTiledMap* GameScene::GetMap()
{
	return _map;
}
BuildingManager*  GameScene::GetBuildingManager()const
{
	return _buildingManager;
}
MenuLayer* GameScene::GetMenuLayer() const
{
	return _menuLayer;
}
MapManager* GameScene::GetMapManager() const
{
	return _mapManager;
}
SoldierManager* GameScene::GetSoldierManager()const
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