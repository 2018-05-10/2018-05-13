#include"MapManager.h"
#include"Scene/GameScene/GameScene.h"

USING_NS_CC;
bool MapManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	for (int i = 0; i < 75; ++i)
	{
		std::vector<int> temp;
		for (int j = 0; j < 75; ++j)
		{
			temp.push_back(1);
		}
		_mapVec.push_back(temp);
	}
	
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


	listener->onMouseDown = [&](Event*) { _isClick = true;

	
	};
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
	auto node = static_cast<GameScene*>(this->getParent())->GetMap();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto currentPos = node->getPosition();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto mapTiledNum =static_cast<GameScene*>(this->getParent())->GetMap()->getMapSize();
	auto tiledSize = static_cast<GameScene*>(this->getParent())->GetMap()->getTileSize()*0.78125;
	
	

	Point mapSize = Point(mapTiledNum.width*tiledSize.width,mapTiledNum.height*tiledSize.height);
	int speed = 20;
	
	

	if ((_key_A_isPressed || _mousePosition.x <visibleSize.width / 6)&&!_isClick)
	{
		if (currentPos.x< 0)
		{
			currentPos += Point(speed, 0);
		}
	}
	if ((_key_D_isPressed || _mousePosition.x >visibleSize.width*0.97) && !_isClick)
	{
		if (currentPos.x + mapSize.x > visibleSize.width)
		{
			currentPos += Point(-speed, 0);
		}
	}
	if ((_key_S_isPressed || _mousePosition.y <visibleSize.height / 6) && !_isClick)
	{
		if (currentPos.y < 0)
		{
			currentPos += Point(0, speed);
		}
	}
	if ((_key_W_isPressed || _mousePosition.y > visibleSize.height*5 / 6) && !_isClick)
	{
		if (currentPos.y + mapSize.y > visibleSize.height)
		{
			currentPos += Point(0, -speed);
		}
	}
	node->setPosition(currentPos);
}
Vec2 MapManager::ChangeToTiledPos(Point pos)
{
	auto mapSize = static_cast<GameScene*>(this->getParent())->GetMap()->getMapSize();
	auto tileSize= static_cast<GameScene*>(this->getParent())->GetMap()->getTileSize()*0.78125;
	float halfMapWidth = mapSize.width * 0.5f;
	float mapHeight = mapSize.height;
	float tileWidth = tileSize.width;
	float tileHeight = tileSize.height;


	Vec2 tilePosDiv = CCPointMake(pos.x / tileWidth, pos.y / tileHeight);
	float inverseTileY = mapHeight - tilePosDiv.y;


	float posX = inverseTileY + tilePosDiv.x - halfMapWidth;
	float posY = inverseTileY - tilePosDiv.x + halfMapWidth;

	if (posX - static_cast<int>(posX) < 0.5)
	{
		posX = static_cast<int>(posX);
	}
	else
	{
		posX = static_cast<int>(posX)+1;
	}

	if (posY - static_cast<int>(posY) < 0.5)
	{
		posY = static_cast<int>(posY);
	}
	else
	{
		posY = static_cast<int>(posY) + 1;
	}

	return Vec2(posX, posY);
}

bool MapManager::BuildingCheck(Point pos)
{
	Vec2 tilePos = ChangeToTiledPos(pos);

	if (tilePos.x < 0 || tilePos.x>74)
	{
		return false;
	}
	if (tilePos.y < 0 || tilePos.y>74)
	{
		return false;
	}

	auto originPos = tilePos - Point(2, 2);
	if ((originPos.x < 0 || originPos.x>70) || (originPos.y < 0 || originPos.y>70))
	{
		return false;
	}
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (_mapVec[static_cast<int>(originPos.x + i)][static_cast<int>(originPos.y + j)] == 0||
				_mapVec[static_cast<int>(originPos.x + i)][static_cast<int>(originPos.y + j)] == 2)
			{
				return false;
			}
		}
	}

	return true;
}

void MapManager::SetTestListener()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		Vec2 pos2 = ChangeToTiledPos(pos- static_cast<GameScene*>(this->getParent())->GetMap()->getPosition());

		log("%f %f", pos2.x, pos2.y);

		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MapManager::GetTiledInformation()
{
	auto map = static_cast<GameScene*>(this->getParent())->GetMap();
	auto meta = map->getLayer("meta");
	for (int i = 0; i < 75; ++i)
	{
		for (int j = 0; j < 75; ++j)
		{
			int tiledGid = meta->getTileGIDAt(Vec2(i, j));
			if (tiledGid)
			{
				Value properties = map->getPropertiesForGID(tiledGid);
				ValueMap propMap = properties.asValueMap();
				if (propMap.find("Collidable") != propMap.end()){
						_mapVec[i][j] = 0;
				}
			}
		}
	}
}

void MapManager::SetBuilding(Point pos)
{
	auto origin = this->ChangeToTiledPos(pos) - Point(2, 2);

	for (int i = -1; i < 6; ++i)
	{
		for (int j = -1; j < 6; ++j)
		{
			if (i == -1 || j == 5)
			{
				_mapVec[origin.x + i][origin.y + j] = 2;
			}
			else
			{
				_mapVec[origin.x + i][origin.y + j] = 0;
			}
		}
	}
	
}

Vec2 MapManager::ChangeToCocosPos(Vec2 pos)
{
	auto mapSize = static_cast<GameScene*>(this->getParent())->GetMap()->getMapSize();
	auto tileSize = static_cast<GameScene*>(this->getParent())->GetMap()->getTileSize()*0.78125;
	int x =pos.x*tileSize.width + (static_cast<int>(pos.y )% 2) *tileSize.width / 2;
	int y = (mapSize.height - (pos.y + 1))*tileSize.height / 2 - tileSize.height / 2;
	return Vec2(x, y);

}