#include "Building.h"

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

//Sprite* Building::Build(char* TypeName)
//{
//	Sprite* a = NULL;
//	a = _pManager->CreateBuilding(TypeName);
//	if (a == NULL)
//	{
//		a = _pManager->GetPairManager()->CreateSoldier(TypeName);
//	}
//	return a;
//}

bool Building::init()
{
	return true;
}

//void Building::Die()
//{
//	_pManager->DestroyBuilding(this);
//}



//========building ID by cyy=====
int Building::buildingsID = 2;

int Building::GetBuildingID()
{
	return buildingsID;
}