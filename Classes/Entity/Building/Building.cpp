#include "Classes/Entity/Building/Building.h"

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

void Building::Build(Entity E)
{

}

bool Building::init()
{
	return true;
}