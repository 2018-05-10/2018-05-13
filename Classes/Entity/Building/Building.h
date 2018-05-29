#pragma once
#include "Classes/Entity/Entity.h"
#include "Classes/Resource/Power.h"
#include "Classes/Resource/Mineral.h"
USING_NS_CC;

class Building :public Entity
{
public:
	Building();
	~Building();
	bool IsWorking();
	void SetIsWorking(bool a);
	void Build(Entity E);
	bool init();
protected:
	bool _isWorking;
	int _powerCost;
	int _mineralCost;
};