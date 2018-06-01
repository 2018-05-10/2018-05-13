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
	_map->setPosition(-1875,-937.5);
	 _mapManager = MapManager::create();
	this->addChild(_mapManager,1);
	_buildingManager = BuildingManager::create();
	this->addChild(_buildingManager, 1);
	_menuLayer = MenuLayer::create();
	this->addChild(_menuLayer, 10);
	_soldierManager = SoldierManager::create();
	this->addChild(_soldierManager, 1);


	


	_mapManager->SetMouseController();
	_mapManager->SetKeyboardController();
	_mapManager->schedule(schedule_selector(MapManager::ControllerUpdate));
	_mapManager->SetTestListener();
	_mapManager->GetTiledInformation();

	_soldierManager->SetSelectBoxController();

	Base* base = Base::create();
	base->BindSprite(Sprite::create("Building/Base.png"));
	_map->addChild(base,1);
	base->setPosition(2000,1000);
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
Size GameScene::GetMapSize()const
{
	auto _ground = _map->getLayer("background");
	auto ZERO_Tile = _ground->getTileAt(Vec2(0, 0));
	auto ONE_Tile = _ground->getTileAt(Vec2(1, 0));
	auto pos1 = ZERO_Tile->getPosition();
	auto pos2 = ONE_Tile->getPosition();
	auto mapTiledNum = _map->getMapSize();
	Size size = Size(abs(pos1.x-pos2.x),abs(pos1.x-pos2.x));

	return Size(mapTiledNum.width*size.width, mapTiledNum.height*size.height);
}
