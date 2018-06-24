#include"SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Entity/Soldier/Infantry.h"
#include"Entity/Soldier/Dog.h"
#include"Entity/Soldier/Tank.h"
#include"Manager/MapManager.h"
#include"Scene\GameScene\MenuLayer.h"
#include"Entity/Soldier/Soldier.h"
#include"Tool\SearchRod.h"
#include<algorithm>
#include<utility>
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace SearchRoad;


bool SoldierManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	
	_selectBox = Sprite::create("selectbox.png");
	this->addChild(_selectBox);
	_selectBox->setOpacity(0);
	_iter = _beChoosedMap.begin();
	//this->schedule(schedule_selector(SoldierManager::update), 0.1f);
	return true;
}

void SoldierManager::SetSelectBoxController()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		for (auto soldier : _beChoosedMap)
		{
			soldier.second->GetSprite()->setColor(Color3B(255, 255, 255));
		}
		_beChoosedMap.clear();
		_selectBox->setOpacity(0);
		_getTouchBeganPos= convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		return true;
	};
	listener->onTouchMoved = [&](Touch *touch, Event *event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_selectBox->setContentSize(Size(abs(originPos.x - _getTouchBeganPos.x), abs(originPos.y - _getTouchBeganPos.y)));
		_selectBox->setPosition(originPos/2+ _getTouchBeganPos/2);
		_selectBox->setOpacity(150);
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event)
	{
		_getTouchEndedPos= convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		for (auto soldier : _soldierMap)
		{
			Point mapPos= GetMap()->getPosition();
			Point pos = soldier.second->getPosition()+mapPos;
			if ((pos.x - _getTouchBeganPos.x)*(pos.x - _getTouchEndedPos.x) < 0
				&& (pos.y - _getTouchBeganPos.y)*(pos.y - _getTouchEndedPos.y) < 0)
			{
				_beChoosedMap.insert(soldier);
				soldier.second->GetSprite()->setColor(Color3B::BLUE);
			}
		}
		_selectBox->setOpacity(0);
		
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void SoldierManager::SetSoldierController(Soldier* soldier)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Soldier*>(event->getCurrentTarget());
		
		if (target1->getBoundingBox().containsPoint(pos -GetMap()->getPosition()))
		{
			_beChoosedMap.clear();
			_beChoosedMap.insert(std::make_pair(target1->GetSoldierID(),target1));
			target1->GetSprite()->setColor(Color3B::BLUE);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, soldier);
}


Soldier* SoldierManager::CreateSoldier(char* SoldierNameType,int player)
{
	Sprite* spr = NULL;
	Soldier* S = NULL;
	if (SoldierNameType == "Dog")
	{
		S = new Dog(_pMineral,player);
		_dogVec.push_back(S);
		S->_numInTypeVec = _dogVec.size() - 1;
		spr = Sprite::createWithSpriteFrameName("Dog_move_(1,0)_1.png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Infantry")
	{
		S = new Infantry(_pMineral,player);
		_infantryVec.push_back(S);
		S->_numInTypeVec = _infantryVec.size() - 1;
		spr = Sprite::createWithSpriteFrameName("Infantry_stand_(1,0).png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Tank")
	{
		S = new Tank(_pMineral,player);
		_tankVec.push_back(S);
		S->_numInTypeVec = _tankVec.size() - 1;
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

void SoldierManager::SetTargetController()
{
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [&](Event* event)
	{
		if (static_cast<int>(static_cast<EventMouse*>(event)->getMouseButton()) == 1)
		{
			Point _getClickPosition;
			_getClickPosition.x = static_cast<EventMouse*>(event)->getCursorX();
			_getClickPosition.y = static_cast<EventMouse*>(event)->getCursorY();

			auto mapPos = GetMap()->getPosition();
			auto mapPoint = GetMapManager()->ChangeToTiledPos(_getClickPosition - mapPos);
			if (mapPoint.x < 0 || mapPoint.x>74 || mapPoint.y < 0 || mapPoint.y>74)
			{
				return;
			}
			if (!MapManager::CheckTargetPos(mapPoint))
			{
				return;
			}
			
			GetMapManager()->TargetPosBFS(_getClickPosition - mapPos);
			for (auto soldier : _beChoosedMap)
			{
				auto tileStart = MapManager::ChangeToTiledPos(soldier.second->getPosition());
				auto tileEnd = MapManager::ChangeToTiledPos(soldier.second->_targetPoint);
				soldier.second->stopAllActions();
				soldier.second->_path.clear();
				startSearch(tileStart, tileEnd, soldier.second);
				Move(soldier.second);
			}
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
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



void SoldierManager::Square(Soldier* soldier)
{
	auto tileStart = GetMapManager()->ChangeToTiledPos(soldier->getPosition());
	auto tileEnd= GetMapManager()->ChangeToTiledPos(soldier->_targetPoint);

	int direction=0;
	soldier->_path.push_back(tileStart);
	if (tileStart.x < tileEnd.x)
	{
		direction = 1;
	}
	else
	{
		direction = -1;
	}
	while (tileStart.x!= tileEnd.x)
	{
		tileStart.x += direction;
		soldier->_path.push_back(tileStart);
	}

	direction = 0;
	if (tileStart.y <tileEnd.y)
	{
		direction = 1;
	}
	else
	{
		direction = -1;
	}
	while (tileStart.y!= tileEnd.y)
	{
		tileStart.y += direction;
		soldier->_path.push_back(tileStart);
	}

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

void SoldierManager::SetEnemyTargetController(Entity* enemy)
{
	auto listener = EventListenerMouse::create();


	listener->onMouseDown = [&,enemy](Event *event)
	{
		if (static_cast<int>(static_cast<EventMouse*>(event)->getMouseButton()) == 1)
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			Point pos;
			pos.x = static_cast<EventMouse*>(event)->getCursorX();
			pos.y = static_cast<EventMouse*>(event)->getCursorY();
			auto target1 = static_cast<Soldier*>(event->getCurrentTarget());

			if (target1->getBoundingBox().containsPoint(pos - GetMap()->getPosition()))
			{
				for (auto soldier : _beChoosedMap)
				{
					soldier.second->_target = enemy;
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, enemy);
}


void SoldierManager::update(float dt)
{
	if (_searchList.empty())
	{
		return;
	}
	while ((_searchList.front()) == nullptr)
	{
		_searchList.pop();
	}
	auto tileStart =MapManager::ChangeToTiledPos((_searchList.front())->getPosition());
	auto tileEnd = MapManager::ChangeToTiledPos((_searchList.front())->_targetPoint);
	(_searchList.front())->stopAllActions();
	(_searchList.front())->_path.clear();
	startSearch(tileStart, tileEnd, (_searchList.front()));
	Move(_searchList.front());
	_searchList.pop();
}

int SearchRoad::countH(JieDian* sJieDian, JieDian* eJieDian)
{
	int w = abs(sJieDian->x - eJieDian->x);
	int h = abs(sJieDian->y - eJieDian->y);
	int cost = std::min(w, h)*xieyi + abs(w - h)*pingyi;//曼哈顿公式简化
	return cost;
}

void SearchRoad::countFGH(JieDian* sJieDian, JieDian* eJieDian, int cost)
{
	int h = countH(sJieDian, eJieDian);
	int g = sJieDian->parent->g + cost;
	int f = h + g;
	sJieDian->f = f;//使起始节点的参数值刷新
	sJieDian->h = h;
	sJieDian->g = g;
}

int SearchRoad::Contains(std::vector<JieDian*>& v, int x, int y)
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
void SearchRoad::releaseJieDian(JieDian* n, Soldier* soldier)
{
	if (n->parent != NULL)
	{
		releaseJieDian(n->parent, soldier);
		auto point = Point(n->x, n->y);
		soldier->_path.push_back(point);
	}
	delete n;
}
bool compare(SearchRoad::JieDian* n1, SearchRoad::JieDian* n2)
{
	return (n1->f) < (n2->f);
}
void SearchRoad::checkMove(int x, int y, JieDian* parent, JieDian* end, int cost)
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
		JieDian* sJieDian = openList[index];
		if (parent->g + cost < sJieDian->g)
		{
			sJieDian->g = parent->g + cost;
			sJieDian->f = sJieDian->g + sJieDian->h;
		}
	}
	else
	{
		JieDian* n = new JieDian(x, y, parent);
		countFGH(n, end, cost);
		openList.push_back(n);
	}
}
int SearchRoad::startSearch(Point startp, Point endp, Soldier* soldier)
{
	JieDian* start = new JieDian(startp.x, startp.y);
	JieDian* end = new JieDian(endp.x, endp.y);
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
	JieDian* root = NULL;
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
	releaseJieDian(root, soldier);
	openList.clear();
	closeList.clear();
	return find;
}

std::unordered_map<int,Soldier*> SoldierManager::_enemySoldierMap;
std::unordered_map<int,Soldier*> SoldierManager::_soldierMap;
std::vector<Soldier*> SoldierManager::_infantryVec;
std::vector<Soldier*> SoldierManager::_tankVec;
std::vector<Soldier*> SoldierManager::_dogVec;
std::unordered_map<int,Soldier*> SoldierManager::_beChoosedMap;
std::queue<Soldier*>SoldierManager::_searchList;
Mineral* SoldierManager::_pMineral;