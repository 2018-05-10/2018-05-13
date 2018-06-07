#include"MapManager.h"
#include"Scene/GameScene/GameScene.h"
#include<queue>
#include<string>
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
	auto node =GetMap();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto currentPos = node->getPosition();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto mapTiledNum =GetMap()->getMapSize();
	auto tiledSize = GetMap()->getTileSize()*0.78125;
	
	
	log("%d", BuildingManager::_mineralPerSecond);
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


bool MapManager::BuildingPositionCheck(Point pos,int name)
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

	auto originPos = tilePos;
	int width, height;
	
	switch (name)
	{
	case(0):
		width = 4;
		height = 4;
		originPos += Point(4, 3);
		break;
	case(1):
		width = 3;
		height = 3;
		originPos += Point(3,3);
		break;
	case(2):
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case(3):
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case(4):
		width = 3;
		height = 3;
		originPos += Point(3, 3);
		break;
	}

	if ((originPos.x < width || originPos.x>74) || (originPos.y < height || originPos.y>74))
	{
		return false;
	}
	for (int i = 0; i < width+1; ++i)
	{
		for (int j = 0; j < height+1; ++j)
		{
			if (_mapVec[static_cast<int>(originPos.x - i)][static_cast<int>(originPos.y - j)] == 0||
				_mapVec[static_cast<int>(originPos.x - i)][static_cast<int>(originPos.y - j)] == 2)
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
		return true;
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event)
	{

		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		Vec2 pos2 = ChangeToTiledPos(pos- GetMap()->getPosition());

		
		
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MapManager::GetTiledInformation()
{
	auto map = GetMap();
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

void MapManager::SetBuilding(Point pos,int name)
{
	auto originPos = ChangeToTiledPos(pos);

	int width, height;

	switch (name)
	{
	case(0):
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case(1):
		width = 3;
		height = 3;
		originPos += Point(3, 3);
		break;
	case(2):
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case(3):
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case(4):
		width = 3;
		height = 3;
		originPos += Point(3, 3);
		break;
	}

	for (int i = -1; i < width+2; ++i)
	{
		for (int j = -1; j < height+2; ++j)
		{
			if (originPos.x - i < 0 || originPos.x - i>74 || originPos.y - j < 0 || originPos.y - j>74)
			{
				continue;
			}
			if ((i == -1 || j == height+1||j==-width+1||i==4)&&_mapVec[originPos.x - i][originPos.y - j]!=0)
			{
				_mapVec[originPos.x - i][originPos.y - j] = 2;
			}
			else
			{
				_mapVec[originPos.x - i][originPos.y - j] = 0;
			}
		}
	}
	
}

Vec2 MapManager::ChangeToTiledPos(Point pos)
{
	auto mapSize = GetMap()->getMapSize();
	auto tileSize = GetMap()->getTileSize()*0.78125;
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
		posX = static_cast<int>(posX) + 1;
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

Vec2 MapManager::ChangeToCocosPos(Vec2 pos)
{
	auto mapSize = GetMap()->getMapSize();
	auto tileSize = GetMap()->getTileSize()*0.78125;
	int x =tileSize.width*(mapSize.width+pos.x-pos.y)/2;
	int y =tileSize.height*mapSize.height- tileSize.height*(pos.x+pos.y)/2 ;
	return Vec2(x, y);

}

Point MapManager::BFS(Point start)
{
	using namespace std;
	int count=0;
	Point tileStart = ChangeToTiledPos(start);

	if (tileStart.x < 0)
	{
		tileStart.x = 0;
	}
	else if (tileStart.x > 74)
	{
		tileStart.x = 74;
	}
	if (tileStart.y < 0)
	{
		tileStart.y = 0;
	}
	else if (tileStart.y > 74)
	{
		tileStart.y = 74;
	}
	int dir[8][2] = { {0,1},{1,0},{1,1},{1,-1},{ 0,-1 },{ -1,0 },{ -1,-1 },{ -1,1 } };
	int searchMap[75][75];
	for (int i = 0; i < 75; ++i)
	{
		for (int j = 0; j < 75; ++j) {
			searchMap[i][j] = 0;
		}
	}
	queue<Point> isSearched;
	isSearched.push(tileStart);
	
	while (!isSearched.empty())
	{
		if (_mapVec[isSearched.front().x][isSearched.front().y] != 0&& _mapVec[isSearched.front().x][isSearched.front().y] != 2)
		{ 
			
			return ChangeToCocosPos(isSearched.front());
		}
		searchMap[static_cast<int>(isSearched.front().x)][static_cast<int>(isSearched.front().y)] = 1;
		for (int i = 0; i < 8; ++i)
		{
			if (static_cast<int>(isSearched.front().x) + dir[i][0] < 0 || static_cast<int>(isSearched.front().x) + dir[i][0]>74 ||
				static_cast<int>(isSearched.front().y) + dir[i][1] < 0 || static_cast<int>(isSearched.front().y) + dir[i][1]>74)
			{
				continue;
			}
			if (!searchMap[static_cast<int>(isSearched.front().x) + dir[i][0]][static_cast<int>(isSearched.front().y) + dir[i][1]])
			{
				
				isSearched.push(Point(isSearched.front().x + dir[i][0], isSearched.front().y + dir[i][1]));
				searchMap[static_cast<int>(isSearched.front().x + dir[i][0])][static_cast<int>(isSearched.front().y) + dir[i][1]] = 1;
			}
			
		}
		
		isSearched.pop();
	
	}
	
	return Point(-1, -1);
}

void MapManager::TargetPosBFS(Point start)
{
	using namespace std;
	Point tileStart =ChangeToTiledPos(start);

	if (SoldierManager::_beChoosed.empty())
	{
		return;
	}

	if (tileStart.x < 0)
	{
		tileStart.x = 0;
	}
	else if (tileStart.x > 74)
	{
		tileStart.x = 74;
	}
	if (tileStart.y < 0)
	{
		tileStart.y = 0;
	}
	else if (tileStart.y > 74)
	{
		tileStart.y = 74;
	}
	int dir[8][2] = { { 0,1 },{ 1,0 },{ 1,1 },{ 1,-1 },{ 0,-1 },{ -1,0 },{ -1,-1 },{ -1,1 } };
	int searchMap[75][75];
	for (int i = 0; i < 75; ++i)
	{
		for (int j = 0; j < 75; ++j) {
			searchMap[i][j] = 0;
		}
	}
	queue<Point> isSearched;
	isSearched.push(tileStart);
	int count = 0;
	while (!isSearched.empty())
	{
		if (_mapVec[isSearched.front().x][isSearched.front().y] != 0&& _mapVec[isSearched.front().x][isSearched.front().y] != 2)
		{
			SoldierManager::_beChoosed.at(count++)->_targetPoint =ChangeToCocosPos( isSearched.front());
			if (count == SoldierManager::_beChoosed.size())
			{
				return;
			}
		}
		searchMap[static_cast<int>(isSearched.front().x)][static_cast<int>(isSearched.front().y)] = 1;
		for (int i = 0; i < 8; ++i)
		{
			if (static_cast<int>(isSearched.front().x) + dir[i][0] < 0 || static_cast<int>(isSearched.front().x) + dir[i][0]>74 ||
				static_cast<int>(isSearched.front().y) + dir[i][1] < 0 || static_cast<int>(isSearched.front().y) + dir[i][1]>74)
			{
				continue;
			}
			if (!searchMap[static_cast<int>(isSearched.front().x) + dir[i][0]][static_cast<int>(isSearched.front().y) + dir[i][1]])
			{

				isSearched.push(Point(isSearched.front().x + dir[i][0], isSearched.front().y + dir[i][1]));
				searchMap[static_cast<int>(isSearched.front().x+dir[i][0])][static_cast<int>(isSearched.front().y)+dir[i][1]] = 1;

			}

		}

		isSearched.pop();
	}
}

void MapManager::SetSoldier(Point pos)
{
	auto origin = this->ChangeToTiledPos(pos);
	_mapVec[origin.x][origin.y] = 2;
	log("%f %f", origin.x, origin.y);
}

TMXTiledMap* MapManager::GetMap()
{
	return 	static_cast<GameScene*>(this->getParent())->GetMap();
}
BuildingManager*  MapManager::GetBuildingManager()
{
	return  static_cast<GameScene*>(this->getParent())->GetBuildingManager();
}
SoldierManager* MapManager::GetSoldierManager()
{
	return static_cast<GameScene*>(this->getParent())->GetSoldierManager();
}
Mineral* MapManager::GetMineral()
{
	return  static_cast<GameScene*>(this->getParent())->GetMineral();
}
Power* MapManager::GetPower()
{
	return  static_cast<GameScene*>(this->getParent())->GetPower();
}