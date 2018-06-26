#include"GameController.h"
#include"Scene\GameScene\GameScene.h"
#include"Manager\SoldierManager.h"
#include"Manager\MapManager.h"
#include"Entity\Soldier\Soldier.h"
#include"Entity\Building\Building.h"
#include"Scene\GameScene\MenuLayer.h"
#include"Entity\Player.h"
USING_NS_CC;

#define BASE 1
#define FACTORY 2
#define BARRACK 3
#define MINE 4
#define POWERSTATION 5
#define INFANTRY 6
#define DOG 7
#define TANK 8
#define CREATE_ENEMY 1000
#define SET_ENEMY_TARGET 1001
#define SET_ENEMY_TARGET_ENEMY 1002

namespace SearchRoad
{
	int startSearch(cocos2d::Point start, cocos2d::Point end, Soldier*);
}

bool GameController::init()
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

void GameController::KeyReleasedEvent(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event)
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


void GameController::KeyPressedEvent(EventKeyboard::KeyCode code, Event *event)
{
	if (code == EventKeyboard::KeyCode::KEY_D)
	{
		_key_D_isPressed = true;

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

void GameController::SetMouseController()
{
	auto listener = EventListenerMouse::create();


	listener->onMouseDown = [&](Event*) { _isClick = true; };
	listener->onMouseMove = [&](Event* event) {
		_mousePosition.x = static_cast<EventMouse*>(event)->getCursorX();
		_mousePosition.y = static_cast<EventMouse*>(event)->getCursorY();
	};
	listener->onMouseUp = [&](Event*) { _isClick = false; };

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, GameScene::GetMap());
}

void GameController::SetKeyboardController()
{
	auto listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(GameController::KeyPressedEvent,this);
	listener->onKeyReleased = CC_CALLBACK_2(GameController::KeyReleasedEvent, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameController::ControllerUpdate(float dt)
{
	auto node = GameScene::GetMap();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto currentPos = node->getPosition();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto mapTiledNum = GameScene::GetMap()->getMapSize();
	auto tiledSize = GameScene::GetMap()->getTileSize()*0.78125;

	Point mapSize = Point(mapTiledNum.width*tiledSize.width, mapTiledNum.height*tiledSize.height);
	int speed = 20;



	if ((_key_A_isPressed || _mousePosition.x <visibleSize.width / 6) && !_isClick)
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
	if ((_key_W_isPressed || _mousePosition.y > visibleSize.height * 5 / 6) && !_isClick)
	{
		if (currentPos.y + mapSize.y > visibleSize.height)
		{
			currentPos += Point(0, -speed);
		}
	}
	node->setPosition(currentPos);
}

void GameController::SetSelectBoxController()
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{
		for (auto soldier : SoldierManager::_beChoosedMap)
		{
			soldier.second->GetSprite()->setColor(Color3B(255, 255, 255));
		}
		SoldierManager::_beChoosedMap.clear();
		_selectBox->setOpacity(0);
		_getTouchBeganPos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		return true;
	};
	listener->onTouchMoved = [&](Touch *touch, Event *event)
	{
		auto originPos = Point(Director::getInstance()->convertToGL(touch->getLocationInView()));
		_selectBox->setContentSize(Size(abs(originPos.x - _getTouchBeganPos.x), abs(originPos.y - _getTouchBeganPos.y)));
		_selectBox->setPosition(originPos / 2 + _getTouchBeganPos / 2);
		_selectBox->setOpacity(150);
	};
	listener->onTouchEnded = [&](Touch *touch, Event *event)
	{
		_getTouchEndedPos = convertToNodeSpace(Director::getInstance()->convertToGL(touch->getLocationInView()));
		for (auto soldier : SoldierManager::_soldierMap)
		{
			Point mapPos = GameScene::GetMap()->getPosition();
			Point pos = soldier.second->getPosition() + mapPos;
			if ((pos.x - _getTouchBeganPos.x)*(pos.x - _getTouchEndedPos.x) < 0
				&& (pos.y - _getTouchBeganPos.y)*(pos.y - _getTouchEndedPos.y) < 0)
			{
				SoldierManager::_beChoosedMap.insert(soldier);
				soldier.second->GetSprite()->setColor(Color3B::BLUE);
			}
		}
		_selectBox->setOpacity(0);

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameController::SetSoldierController(Soldier* soldier)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [&](Touch *touch, Event *event)
	{

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Soldier*>(event->getCurrentTarget());

		if (target1->getBoundingBox().containsPoint(pos -GameScene:: GetMap()->getPosition()))
		{
			SoldierManager::_beChoosedMap.clear();
			SoldierManager::_beChoosedMap.insert(std::make_pair(target1->GetID(), target1));
			target1->GetSprite()->setColor(Color3B::BLUE);
			return true;
		}
		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, soldier);
}

void GameController::SetTargetController()
{
	auto listener = EventListenerMouse::create();
	listener->onMouseDown = [&](Event* event)
	{
		if (static_cast<int>(static_cast<EventMouse*>(event)->getMouseButton()) == 1)
		{
			Point _getClickPosition;
			_getClickPosition.x = static_cast<EventMouse*>(event)->getCursorX();
			_getClickPosition.y = static_cast<EventMouse*>(event)->getCursorY();

			auto mapPos = GameScene::GetMap()->getPosition();
			auto mapPoint = MapManager::ChangeToTiledPos(_getClickPosition - mapPos);
			if (mapPoint.x < 0 || mapPoint.x>74 || mapPoint.y < 0 || mapPoint.y>74)
			{
				return;
			}
			if (!MapManager::CheckTargetPos(mapPoint))
			{
				return;
			}

			GameScene::GetMapManager()->TargetPosBFS(_getClickPosition - mapPos);
			for (auto soldier : SoldierManager::_beChoosedMap)
			{
				auto tileStart = MapManager::ChangeToTiledPos(soldier.second->getPosition());
				auto tileEnd = MapManager::ChangeToTiledPos(soldier.second->_targetPoint);
				Player::getInstance()->client->SendData(tileEnd.x, tileEnd.y, 0, soldier.second->GetID(),
					soldier.second->GetType(), SET_ENEMY_TARGET);
				soldier.second->stopAllActions();
				soldier.second->_path.clear();
				SearchRoad::startSearch(tileStart, tileEnd, soldier.second);
				GameScene::GetSoldierManager()->Move(soldier.second);
			}

		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameController::SetEnemyTargetController(Entity* enemy)
{
	auto listener = EventListenerMouse::create();


	listener->onMouseDown = [&, enemy](Event *event)
	{
		if (static_cast<int>(static_cast<EventMouse*>(event)->getMouseButton()) == 1)
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();
			Point pos;
			pos.x = static_cast<EventMouse*>(event)->getCursorX();
			pos.y = static_cast<EventMouse*>(event)->getCursorY();
			auto target1 = static_cast<Soldier*>(event->getCurrentTarget());

			if (target1->getBoundingBox().containsPoint(pos - GameScene::GetMap()->getPosition()))
			{
				for (auto soldier : SoldierManager::_beChoosedMap)
				{
					Player::getInstance()->client->SendData(0, 0, enemy->GetID(), soldier.second->GetID(),
						soldier.second->GetType(), SET_ENEMY_TARGET_ENEMY);
					soldier.second->_target = enemy;
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, enemy);
}

void GameController::SetBuildingController(Building* building)
{
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = [&, building](Touch *touch, Event *event)
	{

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		auto target1 = static_cast<Sprite*>(event->getCurrentTarget());
		if (target1->getBoundingBox().containsPoint(pos - GameScene::GetMap()->getPosition()))
		{
			if (!building->IsWorking())
			{
				GameScene::GetMenuLayer()->CreateMainLayer();
			}
			else
			{
				switch (building->_type)
				{
				case(BASE):
					GameScene::GetMenuLayer()->CreateContructionLayer();
					break;
				case(FACTORY):
					GameScene::GetMenuLayer()->CreateFactoryLayer(building->GetID());
					break;
				case(BARRACK):
					GameScene::GetMenuLayer()->CreateSoldierLayer(building->GetID());
					break;
				case(MINE):
					GameScene::GetMenuLayer()->CreateMainLayer();
					break;
				case(POWERSTATION):
					GameScene::GetMenuLayer()->CreateMainLayer();
					break;
				}
			}
			return true;
		}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, building);
}