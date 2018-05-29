#include"GameScene.h"
#include"Manager/MapManager.h"
#include"MenuLayer.h"
#include"Manager/MenuLayerManager.h"
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


	auto menuLayer = MenuLayer::create();
	this->addChild(menuLayer,10);
	auto _menuLayer =menuLayer->CreateBasementLayer();
	menuLayer->addChild(_menuLayer);
	menuLayer->setPosition(visibleSize.width*0.7, 0);
	menuLayer->SetBuildingController(menuLayer->_buildings);
	


	auto basement = Sprite::create("Building/basement.png");
	basement->setPosition(visibleSize.width * 2 /3, visibleSize.height * 2/3);
	_map->addChild(basement,1);

	return true;
}

TMXTiledMap* GameScene::GetMap() const
{
	return _map;
}