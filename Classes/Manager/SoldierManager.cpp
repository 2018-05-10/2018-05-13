#include"SoldierManager.h"
#include"Scene/GameScene/GameScene.h"
#include"Entity/Soldier/Infantry.h"
#include"Entity/Soldier/Dog.h"
#include"Entity/Soldier/Tank.h"

USING_NS_CC;

bool SoldierManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	
	_selectBox = Sprite::create("selectbox.jpeg");
	this->addChild(_selectBox);
	_selectBox->setOpacity(0);
	return true;
}

void SoldierManager::SetSelectBoxController()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
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
			Point pos = soldier->getPosition() + soldier->getContentSize() / 2+mapPos;
			if ((pos.x - _getTouchBeganPos.x)*(pos.x - _getTouchEndedPos.x) < 0
				&& (pos.y - _getTouchBeganPos.y)*(pos.y - _getTouchEndedPos.y) < 0)
			{
				_beChoosed.pushBack(soldier);
				
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
			_beChoosed.pushBack(target1);
			
			
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, soldier);
}


Soldier* SoldierManager::CreateSoldier(char* SoldierNameType)
{
	Sprite* spr = NULL;
	Soldier* S = NULL;
	if (SoldierNameType == "Dog")
	{
		S = new Dog();
		_dogVec.pushBack(S);
		S->_numInTypeVec = _dogVec.size() - 1;
		spr = Sprite::create("Dog.png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Infantry")
	{
		S = new Infantry();
		_infantryVec.pushBack(S);
		S->_numInTypeVec = _infantryVec.size() - 1;
		spr = Sprite::create("Infantry.png");
		S->BindSprite(spr);
	}
	else if (SoldierNameType == "Tank")
	{
		S = new Tank();
		_tankVec.pushBack(S);
		S->_numInTypeVec = _tankVec.size() - 1;
		spr = Sprite::create("Tank.png");
		S->BindSprite(spr);
	}
	else
	{
		return NULL;
	}

	_soldierVec.pushBack(S);
	S->_numInVec = _soldierVec.size() - 1;

	return S;
}

Vector<Soldier*> SoldierManager::_soldierVec;
Vector<Soldier*> SoldierManager::_infantryVec;
Vector<Soldier*> SoldierManager::_tankVec;
Vector<Soldier*> SoldierManager::_dogVec;
Vector<Soldier*> SoldierManager::_beChoosed;