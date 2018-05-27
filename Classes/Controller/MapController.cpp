#include"Controller/MapController.h"
#include"Scene/GameScene.h"
#include"Manager/MapManager.h"
USING_NS_CC;



void MapController::SetMouseController(MapManager* manager)
{
	auto listener = EventListenerMouse::create();
	 
	
	if (listener->onMouseDown = CC_CALLBACK_1(MapManager::MouseDownEvent, manager))
	{
		listener->onMouseMove = CC_CALLBACK_1(MapManager::MouseMoveEvent, manager);
	}

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,manager);
}

