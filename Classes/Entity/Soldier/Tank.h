#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Tank :public Soldier
{
public:
	Tank();
	~Tank();
	bool init();

	CREATE_FUNC(Tank);
private:

};