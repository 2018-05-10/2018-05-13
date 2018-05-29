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



void MapManager::KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event)
{
	if (code == EventKeyboard::KeyCode::KEY_D)
	{
		_key_D_isPressed = false;
	}
	if (code == EventKeyboard::KeyCode::KEY_W)
	{
		_key_W_isPressed = false;
	}
	if (code == EventKeyboard::KeyCode::KEY_A)
	{
		_key_A_isPressed = false;
	}
	if (code == EventKeyboard::KeyCode::KEY_S)
	{
		_key_S_isPressed = false;
	}
}


void MapManager::KeyPressedEvent(EventKeyboard::KeyCode code, Event *event)
{
	if (code == EventKeyboard::KeyCode::KEY_D)
	{
		_key_D_isPressed=true;

	}
	if (code == EventKeyboard::KeyCode::KEY_W)
	{
		_key_W_isPressed = true;
	}
	if (code == EventKeyboard::KeyCode::KEY_A)
	{
		_key_A_isPressed = true;
	}
	if (code == EventKeyboard::KeyCode::KEY_S)
	{
		_key_S_isPressed = true;
	}
}

void MapManager::SetMouseController()
{
	auto listener = EventListenerMouse::create();


	listener->onMouseDown = [&](Event*) { _isClick = true; };
	listener->onMouseMove = [&](Event* event) {
		_mousePosition.x = static_cast<EventMouse*>(event)->getCursorX();
		_mousePosition.y = static_cast<EventMouse*>(event)->getCursorY();
	};
	listener->onMouseUp = [&](Event*) { _isClick = false; };

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MapManager::SetKeyboardController()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(MapManager::KeyPressedEvent, this);
	listener->onKeyReleased = CC_CALLBACK_2(MapManager::KeyReleasedEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MapManager::ControllerUpdate(float dt)
{
	auto node = getChildByTag(1);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto currentPos = node->getPosition();
	auto mapTiledNum = _map->getMapSize();
	auto tiledSize = _map->getTileSize();
	Point mapSize = Point(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);
	int speed = 20;

	log("%f %f", currentPos.x, currentPos.y);
	
	

	if ((_key_A_isPressed || _mousePosition.x < visibleSize.width / 6)&&!_isClick)
	{
		if (currentPos.x< 0)
		{
			currentPos += Point(speed, 0);
		}
	}
	if ((_key_D_isPressed || _mousePosition.x > visibleSize.width *5/ 6) && !_isClick)
	{
		if (currentPos.x + mapSize.x >= visibleSize.width)
		{
			currentPos += Point(-speed, 0);
		}
	}
	if ((_key_S_isPressed || _mousePosition.y < visibleSize.height / 6) && !_isClick)
	{
		if (currentPos.y < 0)
		{
			currentPos += Point(0, speed);
		}
	}
	if ((_key_W_isPressed || _mousePosition.y > visibleSize.height*5 / 6) && !_isClick)
	{
		if (currentPos.y + mapSize.y >= visibleSize.height)
		{
			currentPos += Point(0, -speed);
		}
	}
	node->setPosition(currentPos);
}

