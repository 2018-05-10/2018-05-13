#include"ResourceManager.h"
#include"Scene/GameScene/GameScene.h"
#include"BuildingManager.h"

USING_NS_CC;

void ResourceManager::UpdateMineral(float dt)
{
	GetMineral()->_currentVal +=GetBuildingManager()->GetMineralPerSecond();

}

TMXTiledMap* ResourceManager::GetMap()
{
	return 	static_cast<GameScene*>(this->getParent())->GetMap();
}
BuildingManager*  ResourceManager::GetBuildingManager()
{
	return  static_cast<GameScene*>(this->getParent())->GetBuildingManager();
}
SoldierManager* ResourceManager::GetSoldierManager()
{
	return static_cast<GameScene*>(this->getParent())->GetSoldierManager();
}
Mineral* ResourceManager::GetMineral()
{
	return  static_cast<GameScene*>(this->getParent())->GetMineral();
}
Power* ResourceManager::GetPower()
{
	return  static_cast<GameScene*>(this->getParent())->GetPower();
}