#pragma once
#include "Classes/Entity/Soldier/Soldier.h"
USING_NS_CC;

class Dog :public Soldier
{
public:
	Dog();
	/*Dog(Mineral* m, SoldierManager* p);*/
	~Dog();
	bool init();

	CREATE_FUNC(Dog);
private:
};