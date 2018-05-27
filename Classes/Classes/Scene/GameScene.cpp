#include"GameScene.h"
#include"Manager/MapManager.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto _scene = Scene::create();

	auto _layer = GameScene::create();
	_scene->addChild(_layer);

	return _scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto map = MapManager::create();
	this->addChild(map);
	map->schedule(schedule_selector(MapManager::KeyUpdate));
	return true;
}

