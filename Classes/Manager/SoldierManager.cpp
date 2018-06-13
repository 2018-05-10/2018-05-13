#include"SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Entity/Soldier/Infantry.h"
#include"Entity/Soldier/Dog.h"
#include"Entity/Soldier/Tank.h"
#include"Manager/MapManager.h"

USING_NS_CC;

bool SoldierManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	
	_selectBox = Sprite::create("selectbox.png");
	this->addChild(_selectBox);
	_selectBox->setOpacity(0);
	return true;
}

void SoldierManager::SetSelectBoxController()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		for (auto soldier : _beChoosed)
		{
			soldier->GetSprite()->setColor(Color3B(255, 255, 255));
		}
		_beChoosed.clear();
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
		for (auto soldier : _soldierVec)
		{
			Point mapPos= static_cast<GameScene*>(this->getParent())->GetMap()->getPosition();
			Point pos = soldier->getPosition()+mapPos;
			if ((pos.x - _getTouchBeganPos.x)*(pos.x - _getTouchEndedPos.x) < 0
				&& (pos.y - _getTouchBeganPos.y)*(pos.y - _getTouchEndedPos.y) < 0)
			{
				_beChoosed.push_back(soldier);
				soldier->GetSprite()->setColor(Color3B::GREEN);
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
		
		if (target1->getBoundingBox().containsPoint(pos - static_cast<GameScene*>(this->getParent())->GetMap()->getPosition()))
		{
			_beChoosed.clear();
			_beChoosed.push_back(target1);
			target1->GetSprite()->setColor(Color3B::GREEN);
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
		S = new Dog(_pMineral, this,player);
		_dogVec.push_back(S);
		S->_numInTypeVec = _dogVec.size() - 1;
		spr = Sprite::createWithSpriteFrameName("Dog_move_(1,0).png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Infantry")
	{
		S = new Infantry(_pMineral, this,player);
		_infantryVec.push_back(S);
		S->_numInTypeVec = _infantryVec.size() - 1;
		spr = Sprite::createWithSpriteFrameName("Infantry_stand_(1,0).png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Tank")
	{
		S = new Tank(_pMineral, this,player);
		_tankVec.push_back(S);
		S->_numInTypeVec = _tankVec.size() - 1;
		spr = Sprite::createWithSpriteFrameName("Tank_move_(1,0).png");
		S->BindSprite(spr);
	}
	else
	{
		return NULL;
	}

	if (!player)
	{
		_soldierVec.push_back(S);
		S->_numInVec = _soldierVec.size() - 1;
	}
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
			if (!CheckPos(mapPoint))
			{
				return;
			}
			
			GetMapManager()->TargetPosBFS(_getClickPosition - mapPos);
			for (auto soldier : _beChoosed)
			{
			
				soldier->stopAllActions();
				soldier->_path.clear();
				Square(soldier);
				Move(soldier);
			
			}

			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}


void SoldierManager::ClearAll()
{
	Soldier* S = NULL;
	for (int i = 0; i < _soldierVec.size(); i++)
	{
		S = _soldierVec.at(i);
		if (S != NULL)
		{
			delete S;
		}
	}
}

void SoldierManager::DestroySoldier(Soldier* S)
{

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
	return 	static_cast<GameScene*>(this->getParent())->GetMap();
}
BuildingManager*  SoldierManager::GetBuildingManager()
{
	return  static_cast<GameScene*>(this->getParent())->GetBuildingManager();
}
MapManager* SoldierManager::GetMapManager()
{
	return static_cast<GameScene*>(this->getParent())->GetMapManager();
}
Mineral* SoldierManager::GetMineral()
{
	return  static_cast<GameScene*>(this->getParent())->GetMineral();
}
Power* SoldierManager::GetPower()
{
	return  static_cast<GameScene*>(this->getParent())->GetPower();
}

bool SoldierManager::CheckPos(Point point)
{
	if (GetMapManager()->_mapVec[point.x][point.y] == 0|| GetMapManager()->_objectVec[point.x][point.y] == 0)
	{
		return false;
	}
	return true;
}

void SoldierManager::Move(Soldier* soldier)
{
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
		if (!CheckPos(soldier->_path[1]))
		{
			
			soldier->_targetPoint = Point(-1, -1);
			return;
		}

		GetMapManager()->SoldierDoMove(soldier->_path[0], soldier->_path[1]);
		soldier->_path.pop_front();
	
		auto nextPos =GetMapManager()->ChangeToCocosPos(soldier->_path.front());

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

std::vector<Soldier*> SoldierManager::_enemySoldierVec;
std::vector<Soldier*> SoldierManager::_soldierVec;
std::vector<Soldier*> SoldierManager::_infantryVec;
std::vector<Soldier*> SoldierManager::_tankVec;
std::vector<Soldier*> SoldierManager::_dogVec;
std::vector<Soldier*> SoldierManager::_beChoosed;