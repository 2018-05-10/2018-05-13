#include"SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Entity/Soldier/Infantry.h"
#include"Entity/Soldier/Dog.h"
#include"Entity/Soldier/Tank.h"
#include"Manager/MapManager.h"
#include"Scene\GameScene\MenuLayer.h"
#include"Entity/Soldier/Soldier.h"
#include"Tool\SearchRoad.h"
#include<algorithm>
#include<utility>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;



bool SoldierManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	

	//this->schedule(schedule_selector(SoldierManager::update), 0.1f);
	return true;
}



Soldier* SoldierManager::CreateSoldier(char* SoldierNameType,int player)
{
	Sprite* spr = NULL;
	Soldier* S = NULL;
	if (SoldierNameType == "Dog")
	{
		S = new Dog(_pMineral,player);
		spr = Sprite::createWithSpriteFrameName("Dog_move_(1,0)_1.png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Infantry")
	{
		S = new Infantry(_pMineral,player);
		spr = Sprite::createWithSpriteFrameName("Infantry_stand_(1,0).png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Tank")
	{
		S = new Tank(_pMineral,player);
		spr = Sprite::createWithSpriteFrameName("Tank_move_(1,1).png");
		S->BindSprite(spr);
	}
	else
	{
		return NULL;
	}
	S->autorelease();
	S->_hpBar = Sprite::createWithSpriteFrameName("GreenBar.png");
	S->addChild(S->_hpBar);
	S->_hpBar->setContentSize(Size(40, 5));
	S->_hpBar->setPosition(35, 60);
	S->_hpBar->setGlobalZOrder(9);
	_soldierMap.insert(std::make_pair(S->GetSoldierID(),S));



	return S;
}


void SoldierManager::ClearAll()
{

	for (auto soldier:_soldierMap)
	{
			soldier.second->removeFromParent();
	}
}

void SoldierManager::DestroySoldier(Soldier* S)
{
	if (S->_player)
	{
		_enemySoldierMap.erase(S->GetSoldierID());
	}
	else
	{
		_soldierMap.erase(S->GetSoldierID());
		if (_beChoosedMap.find(S->GetSoldierID()) != _beChoosedMap.end())
		{

			_beChoosedMap.erase(S->GetSoldierID());
		}
	}

	if (S->_player)
	{
		for (auto soldier : SoldierManager::_soldierMap)
		{
			if (soldier.second->_target == S)
			{
				soldier.second->_target = nullptr;
			}
		}
	}
	else
	{
		for (auto soldier : SoldierManager::_enemySoldierMap)
		{
			if (soldier.second->_target == S)
			{
				soldier.second->_target = nullptr;
			}
		}
	}
	S->removeFromParent();
}

void SoldierManager::SetPlayer(int num)
{
	_player = num;
}

int SoldierManager::GetPlayer()
{
	return _player;
}

void SoldierManager::SetPairManager(BuildingManager* Pair)
{
	_pPairManager = Pair;
}

BuildingManager* SoldierManager::GetPairManager()
{
	return _pPairManager;
}

void SoldierManager::BindMineral(Mineral* m)
{
	_pMineral = m;
}

bool SoldierManager::CheckSoldierResource(char* type)
{
	int mineralCost;
	if (type == "Tank")
	{
		mineralCost = 50;
	}
	else if (type == "Infantry")
	{
		mineralCost = 20;
	}
	else if (type == "Dog")
	{
		mineralCost = 10;
	}
	if (GetMineral()->GetCurrentVal() -mineralCost >= 0)
	{
		return true;
	}
	return false;
}

TMXTiledMap* SoldierManager::GetMap()
{
	return 	GameScene::GetMap();
}
BuildingManager*  SoldierManager::GetBuildingManager()
{
	return GameScene::GetBuildingManager();
}
MapManager* SoldierManager::GetMapManager()
{
	return GameScene::GetMapManager();
}
Mineral* SoldierManager::GetMineral()
{
	return GameScene::GetMineral();
}
Power* SoldierManager::GetPower()
{
	return GameScene::GetPower();
}



void SoldierManager::Move(Soldier* soldier)
{
	if (soldier->_isDead)
	{
		return;
	}
	soldier->GetSprite()->stopAllActions();
	if (soldier != nullptr)
	{

		if (soldier->_targetPoint == Point(-1, -1))
		{
			return;
		}
		if (soldier->_path.empty() || soldier->_path.front() == soldier->_path.back())
		{

		
			soldier->_targetPoint = Point(-1, -1);
			return;
		}
		if (!MapManager::CheckPos(soldier->_path[1]))
		{
			soldier->_path.clear();
			SearchRoad::startSearch(MapManager::ChangeToTiledPos(soldier->getPosition()),
				MapManager::ChangeToTiledPos( soldier->_targetPoint), soldier);
			Move(soldier);
			return;
		}

		MapManager::SoldierDoMove(soldier->_path[0], soldier->_path[1]);
		soldier->_path.pop_front();
	
		auto nextPos =MapManager::ChangeToCocosPos(soldier->_path.front());

		auto moveTo = MoveTo::create(1.0f/static_cast<float>(soldier->GetSpeed()), nextPos);
		auto func = [&,soldier]()
		{
			Move(soldier);
		};
		auto callFunc = CallFunc::create(func);
		soldier->GetSprite()->runAction(soldier->AnimateMove(nextPos));
		auto actions = Sequence::create(moveTo, callFunc,NULL);
		soldier->runAction(actions);

	}
}

Soldier *SoldierManager::CreateEnemySoldier(char* SoldierNameType, int player)
{
	Sprite* spr = NULL;
	Soldier* S = NULL;
	if (SoldierNameType == "Dog")
	{
		S = new Dog( player);
		spr = Sprite::createWithSpriteFrameName("Dog_move_(1,0)_1.png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Infantry")
	{
		S = new Infantry(player);
		spr = Sprite::createWithSpriteFrameName("Infantry_stand_(1,0).png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Tank")
	{
		S = new Tank(player);
		spr = Sprite::createWithSpriteFrameName("Tank_move_(1,0).png");
		S->BindSprite(spr);
	}
	else
	{
		return NULL;
	}
	S->autorelease();
	S->_hpBar = Sprite::createWithSpriteFrameName("RedBar.png");
	S->addChild(S->_hpBar);
	S->_hpBar->setContentSize(Size(40, 5));
	S->_hpBar->setPosition(35, 60);
	_enemySoldierMap.insert(std::make_pair(S->GetSoldierID(),S));


	return S;
}




void SoldierManager::update(float dt)
{
}

int SearchRoad::countH(SearchRoad::Node* sNode, SearchRoad::Node* eNode)
{
	int w = abs(sNode->x - eNode->x);
	int h = abs(sNode->y - eNode->y);
	int cost = std::min(w, h)*xieyi + abs(w - h)*pingyi;//曼哈顿公式简化
	return cost;
}

void SearchRoad::countFGH(SearchRoad::Node* sNode, SearchRoad::Node* eNode, int cost)
{
	int h = countH(sNode, eNode);
	int g = sNode->parent->g + cost;
	int f = h + g;
	sNode->f = f;//使起始节点的参数值刷新
	sNode->h = h;
	sNode->g = g;
}

int SearchRoad::Contains(std::vector<SearchRoad::Node*>& v, int x, int y)
{
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		if ((*it)->x == x && (*it)->y == y)
		{
			return it - v.begin();
		}
	}
	return -1;

}
void SearchRoad::releaseNode(SearchRoad::Node* n, Soldier* soldier)
{
	if (n->parent != NULL)
	{
		releaseNode(n->parent, soldier);
		auto point = Point(n->x, n->y);
		soldier->_path.push_back(point);
	}
	delete n;
}
bool compare(SearchRoad::Node* n1, SearchRoad::Node* n2)
{
	return (n1->f) < (n2->f);
}
void SearchRoad::checkMove(int x, int y, SearchRoad::Node* parent, SearchRoad::Node* end, int cost)
{
	if (MapManager::_mapVec[x][y] == 0 || MapManager::_objectVec[x][y] == 0)
	{
		return;
	}
	if (Contains(closeList, x, y) != -1) //在不能走的地方找到了目的地，这是不合理的
	{
		return;
	}
	int index = 0;
	if ((index = Contains(openList, x, y)) != -1)
	{
		//是否存在更小的G值  
		SearchRoad::Node* sNode = openList[index];
		if (parent->g + cost < sNode->g)
		{
			sNode->g = parent->g + cost;
			sNode->f = sNode->g + sNode->h;
		}
	}
	else
	{
		SearchRoad::Node* n = new SearchRoad::Node(x, y, parent);
		countFGH(n, end, cost);
		openList.push_back(n);
	}
}
int SearchRoad::startSearch(Point startp, Point endp, Soldier* soldier)
{
	SearchRoad::Node* start = new SearchRoad::Node(startp.x, startp.y);
	SearchRoad::Node* end = new SearchRoad::Node(endp.x, endp.y);
	if (start->x <= 0 || start->y <= 0 || start->x > row || start->y > col || end->x <= 0 || end->y <= 0 || end->x > row || end->y > col)
	{
		return -1;
	}//触及边界
	if (MapManager::_mapVec[start->x][start->y] == 0 || MapManager::_mapVec[end->x][end->y] == 0 || MapManager::_objectVec[start->x][start->y] == 0 || MapManager::_objectVec[end->x][end->y] == 0)
	{
		return -1;
	}//起始点有障碍物
	soldier->_path.push_back(startp);
	start->h = countH(start, end);
	start->f = start->h + start->g;
	//查找算法  
	openList.push_back(start);
	SearchRoad::Node* root = NULL;
	int find = 0;
	while (!openList.empty())
	{
		root = openList[0];
		if (root->x == end->x&&root->y == end->y) //找到了
		{
			find = 1;
			break;
		}
		//上下左右   
		if (root->x > 1)
		{
			checkMove(root->x - 1, root->y, root, end, pingyi);
		}
		if (root->y > 1)
		{
			checkMove(root->x, root->y - 1, root, end, pingyi);
		}
		if (root->x < row)
		{
			checkMove(root->x + 1, root->y, root, end, pingyi);
		}
		if (root->y < col)
		{
			checkMove(root->x, root->y + 1, root, end, pingyi);
		}
		if (root->x < row  && root->y > 1)
		{
			checkMove(root->x + 1, root->y - 1, root, end, xieyi);
		}
		if (root->y < col  && root->x > 1)
		{
			checkMove(root->x - 1, root->y + 1, root, end, xieyi);
		}
		if (root->x > 1 && root->y > 1)
		{
			checkMove(root->x - 1, root->y - 1, root, end, xieyi);
		}
		if (root->y < col && root->x < row)
		{
			checkMove(root->x + 1, root->y + 1, root, end, xieyi);
		}
		closeList.push_back(root);
		openList.erase(openList.begin());
		std::sort(openList.begin(), openList.end(), compare);
	}
	releaseNode(root, soldier);
	openList.clear();
	closeList.clear();
	return find;
}

std::unordered_map<int,Soldier*> SoldierManager::_enemySoldierMap;
std::unordered_map<int,Soldier*> SoldierManager::_soldierMap;
std::unordered_map<int,Soldier*> SoldierManager::_beChoosedMap;
Mineral* SoldierManager::_pMineral;