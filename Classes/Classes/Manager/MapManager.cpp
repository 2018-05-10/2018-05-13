#include"MapManager.h"

USING_NS_CC;
bool MapManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	_map = TMXTiledMap::create("map.tmx");
	this->addChild(_map,0,1);
	this->SetMouseController();
	this->SetKeyboardController();
	
	return true;
}

void MapManager::MouseMoveEvent(EventMouse  *event)
{
	int speed = 20;
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto mapTiledNum = _map->getMapSize();
	auto tiledSize = _map->getTileSize();
	Point mapSize = Point(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	auto positionX = event->getCursorX();
	auto positionY = event->getCursorY();

	auto node = getChildByTag(1);
	auto currentPos = node->getPosition();
	
		if (positionX <= visibleSize.width / 6)
		{
			if (currentPos.x< 0)
			{
				currentPos += Point(speed, 0);
			}
			node->setPosition(currentPos);

		}
		else if (positionX >= visibleSize.width / 6 * 5)
		{
			if (currentPos.x + mapSize.x >= visibleSize.width)
			{
				currentPos += Point(-speed, 0);
			}
			node->setPosition(currentPos);
		}

		if (positionY <= visibleSize.height / 6)
		{
			if (currentPos.y<0)
			{
				currentPos += Point(0, speed);
			}
			node->setPosition(currentPos);
		}
		else if (positionY >= visibleSize.height / 6 * 5)
		{
			if (currentPos.y+ mapSize.y >= visibleSize.height)
			{
				currentPos += Point(0, -speed);
			}
			node->setPosition(currentPos);
		}
	
}

void MapManager::KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event)
{
	if (code == EventKeyboard::KeyCode::KEY_D)
	{
		_mapScrScrollSpeed += Vec2(20, 0);
	}
	if (code == EventKeyboard::KeyCode::KEY_W)
	{
		_mapScrScrollSpeed += Vec2(0, 20);
	}
	if (code == EventKeyboard::KeyCode::KEY_A)
	{
		_mapScrScrollSpeed -= Vec2(20, 0);
	}
	if (code == EventKeyboard::KeyCode::KEY_S)
	{
		_mapScrScrollSpeed -= Vec2(0, 20);
	}
}


void MapManager::KeyPressedEvent(EventKeyboard::KeyCode code,Event *event)
{
	log("D");
	if (code == EventKeyboard::KeyCode::KEY_D)
	{
		_mapScrScrollSpeed -= Vec2(20, 0);
		
	}
	if (code == EventKeyboard::KeyCode::KEY_W)
	{
		_mapScrScrollSpeed -= Vec2(0, 20);
	}
	if (code == EventKeyboard::KeyCode::KEY_A)
	{
		_mapScrScrollSpeed += Vec2(20,0);
	}
	if (code == EventKeyboard::KeyCode::KEY_S)
	{
		_mapScrScrollSpeed += Vec2(0,20);
	}
}

void MapManager::SetMouseController()
{
	auto listener = EventListenerMouse::create();


	if (listener->onMouseDown = [&](Event*) {})
	{
		listener->onMouseMove = CC_CALLBACK_1(MapManager::MouseMoveEvent, this);
	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MapManager::SetKeyboardController()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(MapManager::KeyPressedEvent, this);
	listener->onKeyReleased = CC_CALLBACK_2(MapManager::KeyReleasedEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MapManager::KeyUpdate(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto currentPos = _map->getPosition();
	auto mapTiledNum = _map->getMapSize();
	auto tiledSize = _map->getTileSize();
	Point mapSize = Point(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);

	_map->setPosition(currentPos + _mapScrScrollSpeed);
	if (currentPos.x >= 0)
	{
		_map->setPosition(currentPos-Point(1,0));
	}
	if (currentPos.x + mapSize.x <= visibleSize.width)
	{
		_map->setPosition(currentPos + Point(1, 0));
	}
	if (currentPos.y>=0)
	{
		_map->setPosition(currentPos - Point(0,1));
	}
	if (currentPos.y + mapSize.y <= visibleSize.height)
	{
		_map->setPosition(currentPos + Point(0, 1));
	}
}