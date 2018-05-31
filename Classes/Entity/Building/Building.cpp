#include "Heads.h"

Building::Building() {}

Building::~Building() {}

bool Building::IsWorking()
{
	return _isWorking;
}

void Building::SetIsWorking(bool a)
{
	_isWorking = a;
}

Sprite* Building::Build(char* TypeName)
{
	Sprite* a = NULL;
	a = _pManager->CreateBuilding(TypeName);
	if (a == NULL)
	{
		a = _pManager->GetPairManager()->CreateSoldier(TypeName);
	}
	return a;
}

bool Building::init()
{
	return true;
}

void Building::Die()
{
	_pManager->DestroyBuilding(this);
}