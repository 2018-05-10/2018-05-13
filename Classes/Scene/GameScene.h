/*��Ϸ��Ҫ������*/

#pragma once
#include "cocos2d.h"
class GameScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);

	
	cocos2d::TMXTiledMap* GetMap()const;
private:
	cocos2d::Sprite *target;
	cocos2d::TMXTiledMap* _map;
};