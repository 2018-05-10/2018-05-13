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

	auto map = MapManager::create();
	this->addChild(map);
	map->schedule(schedule_selector(MapManager::ControllerUpdate));


	auto menuLayer = MenuLayer::create();
	menuLayer->setPosition(Point(visibleSize.width * 3/4, 0));
	this->addChild(menuLayer);
	return true;
}

