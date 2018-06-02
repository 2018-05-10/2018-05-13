#pragma once
#include"cocos2d.h"
#include"Entity/Building/Building.h"
class BuildingManager :public cocos2d::Node
{
public:
	CREATE_FUNC(BuildingManager);
	

	void SetBaseController(Building*);
	void SetBarrackController(Building*);
	void SetFactoryController(Building*);
	void SetProducerController(Building*);
private:

};