#include"GameScene.h"
#include"MenuLayer.h"
#include"Entity/Building/Base.h"
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
	 _mapManager = MapManager::create();
	this->addChild(_mapManager,-1);
	_buildingManager = BuildingManager::create();
	this->addChild(_buildingManager, -1);
	_menuLayer = MenuLayer::create();
	this->addChild(_menuLayer, 10);
	
	_mapManager->SetMouseController();
	_mapManager->SetKeyboardController();
	_mapManager->schedule(schedule_selector(MapManager::ControllerUpdate));

	Base* base = Base::create();
	base->BindSprite(Sprite::create("Building/Base.png"));
	_map->addChild(base);
	base->setPosition(700, 200);
	_buildingManager->SetBaseController(base);
	

	return true;
}

TMXTiledMap* GameScene::GetMap() const
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