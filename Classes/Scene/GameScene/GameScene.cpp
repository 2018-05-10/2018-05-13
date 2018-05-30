#include"GameScene.h"
#include"Manager/MapManager.h"
#include"MenuLayer.h"
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
	this->addChild(_map,0,1);
	auto mapManager = MapManager::create();
	this->addChild(mapManager);
	
	mapManager->SetMouseController();
	mapManager->SetKeyboardController();
	mapManager->schedule(schedule_selector(MapManager::ControllerUpdate));


	 _menuLayer = MenuLayer::create();
	this->addChild(_menuLayer,10);
	_menuLayer->ClearLayer();
	_menuLayer->CreateBaseLayer();
	
	

	return true;
}

TMXTiledMap* GameScene::GetMap() const
{
	return _map;
}