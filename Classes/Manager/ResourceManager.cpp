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
	return 	GameScene::GetMap();
}
BuildingManager*  ResourceManager::GetBuildingManager()
{
	return 	GameScene::GetBuildingManager();
}
SoldierManager* ResourceManager::GetSoldierManager()
{
	return 	GameScene::GetSoldierManager();
}
Mineral* ResourceManager::GetMineral()
{
	return  	GameScene::GetMineral();
}
Power* ResourceManager::GetPower()
{
	return  	GameScene::GetPower();
}