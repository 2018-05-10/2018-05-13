#include"MapManager.h"
#include"Scene/GameScene/GameScene.h"
#include"SoldierManager.h"
#include"Entity/Building/Building.h"
#include"Entity\Soldier\Soldier.h"
#include"Entity/Player.h"
#include<queue>
#include<string>
USING_NS_CC;

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8


bool MapManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	for (int i = 0; i < Player::getInstance()->getMapSize(); ++i)
	{
		std::vector<int> temp;
		for (int j = 0; j <Player::getInstance()->getMapSize(); ++j)
		{
			temp.push_back(1);
		}
		_mapVec.push_back(temp);
		_objectVec.push_back(temp);
	}
	

	return true;
}







bool MapManager::BuildingPositionCheck(Point pos,int name)
{
	Vec2 tilePos = ChangeToTiledPos(pos);

	if (tilePos.x < 0 || tilePos.x>Player::getInstance()->getMapSize()-1)
	{
		return false;
	}
	if (tilePos.y < 0 || tilePos.y>Player::getInstance()->getMapSize()-1)
	{
		return false;
	}

	auto originPos = tilePos;
	int width, height;
	
	switch (name)
	{
	case(BASE):
		width = 4;
		height = 4;
		originPos += Point(4, 3);
		break;
	case(FACTORY):
		width = 3;
		height = 3;
		originPos += Point(3,3);
		break;
	case(BARRACK):
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case(MINE):
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case(POWERSTATION):
		width = 3;
		height = 3;
		originPos += Point(3, 3);
		break;
	}

	if ((originPos.x < width || originPos.x>Player::getInstance()->getMapSize()-1) || (originPos.y < height || originPos.y>Player::getInstance()->getMapSize()-1))
	{
		return false;
	}
	for (int i = 0; i < width+1; ++i)
	{
		for (int j = 0; j < height+1; ++j)
		{
			if (_mapVec[static_cast<int>(originPos.x - i)][static_cast<int>(originPos.y - j)] == 0||
				_objectVec[static_cast<int>(originPos.x - i)][static_cast<int>(originPos.y - j)] !=1)
			{
				return false;
			}
		}
	}

	return true;
}


void MapManager::GetTiledInformation()
{
	auto map = GetMap();
	auto meta = map->getLayer("meta");
	for (int i = 0; i <Player::getInstance()->getMapSize(); ++i)
	{
		for (int j = 0; j <Player::getInstance()->getMapSize(); ++j)
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
	case BASE:
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case FACTORY:
		width = 3;
		height = 3;
		originPos += Point(3, 3);
		break;
	case BARRACK:
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case MINE:
		width = 4;
		height = 4;
		originPos += Point(3, 3);
		break;
	case POWERSTATION:
		width = 3;
		height = 3;
		originPos += Point(3, 3);
		break;
	}
	for (int i = 0; i < width+1; ++i)
	{
		for (int j = 0; j < height+1; ++j)
		{
			if (originPos.x - i < 0 || originPos.x - i>Player::getInstance()->getMapSize()-1 || 
				originPos.y - j < 0 || originPos.y - j>Player::getInstance()->getMapSize()-1)
			{
				continue;
			}
			_objectVec[originPos.x - i][originPos.y - j] = 0;
			
		}
	}
	
}

void MapManager::RemoveBuilding(Building* building, int name)
{
	auto pos = building->getPosition();
	auto originPos = ChangeToTiledPos(pos);

	int width, height;

	switch (name)
	{
	case BASE:
			width = 4;
			height = 4;
			originPos += Point(3, 3);
			break;
		
	case FACTORY:
			width = 3;
			height = 3;
			originPos += Point(3, 3);
			break;
	case BARRACK:
			width = 4;
			height = 4;
			originPos += Point(3, 3);
			break;
	case MINE:
			width = 4;
			height = 4;
			originPos += Point(3, 3);
			break;
	case POWERSTATION:
			width = 3;
			height = 3;
			originPos += Point(3, 3);
			break;
	}
	for (int i = 0; i < width + 1; ++i)
	{
		for (int j = 0; j < height + 1; ++j)
		{
			if (originPos.x - i < 0 || originPos.x - i>Player::getInstance()->getMapSize()-1 || originPos.y - j < 0 || originPos.y - j>Player::getInstance()->getMapSize()-1)
			{
				continue;
			}
			_objectVec[originPos.x - i][originPos.y - j] = 1;

		}
	}
}

void MapManager::RemoveSoldier(Soldier* soldier)
{
	if (soldier->_path.empty())
	{
		auto pos = soldier->getPosition();
		auto originPos = ChangeToTiledPos(pos);
		_objectVec[originPos.x][originPos.y] = 1;
	}
	else
	{
		if (soldier->_path.front() == soldier->_path.back())
		{
			_objectVec[soldier->_path.front().x][soldier->_path.front().y] = 1;
		}
		else
		{
			_objectVec[soldier->_path[1].x][soldier->_path[1].y] = 1;
		}
	}
}

Vec2 MapManager::ChangeToTiledPos(Point pos)
{
	auto mapSize = GameScene::GetMap()->getMapSize();
	auto tileSize = GameScene::GetMap()->getTileSize()*0.78125;
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
	auto mapSize = GameScene::GetMap()->getMapSize();
	auto tileSize = GameScene::GetMap()->getTileSize()*0.78125;
	int x =tileSize.width*(mapSize.width+pos.x-pos.y)/2;
	int y =tileSize.height*mapSize.height- tileSize.height*(pos.x+pos.y)/2 ;
	return Vec2(x, y);

}

Point MapManager::BFS(Point start)
{
	using namespace std;
	int count=0;
	Point tileStart = ChangeToTiledPos(start-Point(1,1));

	if (tileStart.x < 0)
	{
		tileStart.x = 0;
	}
	else if (tileStart.x > Player::getInstance()->getMapSize()-1)
	{
		tileStart.x = Player::getInstance()->getMapSize()-1;
	}
	if (tileStart.y < 0)
	{
		tileStart.y = 0;
	}
	else if (tileStart.y > Player::getInstance()->getMapSize()-1)
	{
		tileStart.y = Player::getInstance()->getMapSize()-1;
	}
	int dir[8][2] = { {0,1},{1,0},{1,1},{1,-1},{ 0,-1 },{ -1,0 },{ -1,-1 },{ -1,1 } };
	std::vector<std::vector<int>> searchMap;
	for(int i = 0; i < Player::getInstance()->getMapSize(); ++i)
	{
		std::vector<int> temp;
		for (int j = 0; j <Player::getInstance()->getMapSize(); ++j)
		{
			temp.push_back(0);
		}
		searchMap.push_back(temp);
	}
	queue<Point> isSearched;
	isSearched.push(tileStart);
	
	while (!isSearched.empty())
	{
		if (_mapVec[isSearched.front().x][isSearched.front().y] != 0&& _objectVec[isSearched.front().x][isSearched.front().y] != 2
			&& _objectVec[isSearched.front().x][isSearched.front().y] != 0)
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

	if (SoldierManager::_beChoosedMap.empty())
	{
		return;
	}

	for (auto soldier : SoldierManager::_beChoosedMap)
	{
		_objectVec[ChangeToTiledPos(soldier.second->getPosition()).x][ChangeToTiledPos(soldier.second->getPosition()).y] = 1;
	}

	if (tileStart.x < 0)
	{
		tileStart.x = 0;
	}
	else if (tileStart.x > Player::getInstance()->getMapSize()-1)
	{
		tileStart.x = Player::getInstance()->getMapSize() - 1;
	}
	if (tileStart.y < 0)
	{
		tileStart.y = 0;
	}
	else if (tileStart.y > Player::getInstance()->getMapSize() - 1)
	{
		tileStart.y = Player::getInstance()->getMapSize() - 1;
	}
	int dir[8][2] = { { 0,1 },{ 1,0 },{ 1,1 },{ 1,-1 },{ 0,-1 },{ -1,0 },{ -1,-1 },{ -1,1 } };
	std::vector<std::vector<int>> searchMap;
	for (int i = 0; i < Player::getInstance()->getMapSize(); ++i)
	{
		std::vector<int> temp;
		for (int j = 0; j <Player::getInstance()->getMapSize(); ++j)
		{
			temp.push_back(0);
		}
		searchMap.push_back(temp);
	}
	queue<Point> isSearched;
	isSearched.push(tileStart);
	auto iter = SoldierManager::_beChoosedMap.begin();
	while (!isSearched.empty())
	{
		if (_mapVec[isSearched.front().x][isSearched.front().y] != 0&& _objectVec[isSearched.front().x][isSearched.front().y] != 2
			&& _objectVec[isSearched.front().x][isSearched.front().y] != 0)
		{
			iter->second->_targetPoint =ChangeToCocosPos( isSearched.front());
			++iter;
			if (iter == SoldierManager::_beChoosedMap.end())
			{
				return;
			}
		}
		searchMap[static_cast<int>(isSearched.front().x)][static_cast<int>(isSearched.front().y)] = 1;
		for (int i = 0; i < 8; ++i)
		{
			if (static_cast<int>(isSearched.front().x) + dir[i][0] < 0 || static_cast<int>(isSearched.front().x) + dir[i][0]> Player::getInstance()->getMapSize()-1 ||
				static_cast<int>(isSearched.front().y) + dir[i][1] < 0 || static_cast<int>(isSearched.front().y) + dir[i][1]> Player::getInstance()->getMapSize() - 1)
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

void MapManager::ClearAll()
{
	_mapVec.clear();
	_objectVec.clear();
}

bool MapManager::CheckPos(Point point)
{
	if (_mapVec[point.x][point.y] == 0 ||_objectVec[point.x][point.y] == 0)
	{
		return false;
	}
	return true;
}
bool MapManager::CheckTargetPos(Point point)
{
	if (_mapVec[point.x][point.y] == 0)
	{
		return false;
	}
	return true;
}

void MapManager::SetSoldier(Point pos)
{
	auto origin = this->ChangeToTiledPos(pos);
	_objectVec[origin.x][origin.y] = 2;
}

void MapManager:: SoldierDoMove(Point pos1, Point pos2)
{
	_objectVec[pos1.x][pos1.y] = 1;
	_objectVec[pos2.x][pos2.y] = 2;
}

TMXTiledMap* MapManager::GetMap()
{
	return 	GameScene::GetMap();
}
BuildingManager*  MapManager::GetBuildingManager()
{
	return  	GameScene::GetBuildingManager();
}
SoldierManager* MapManager::GetSoldierManager()
{
	return 	GameScene::GetSoldierManager();
}
Mineral* MapManager::GetMineral()
{
	return  	GameScene::GetMineral();
}
Power* MapManager::GetPower()
{
	return  	GameScene::GetPower();
}

std::vector<std::vector<int>> MapManager::_mapVec;
std::vector<std::vector<int>> MapManager::_objectVec;