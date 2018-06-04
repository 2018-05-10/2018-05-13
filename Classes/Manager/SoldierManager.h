#pragma once
#include"cocos2d.h"
#include"Entity/Soldier/Soldier.h"

class SoldierManager :public cocos2d::Node
{

	//=========by cyy==========
public:
	CREATE_FUNC(SoldierManager);
	virtual bool init();

	void SetSelectBoxController();
	void SetSoldierController(Soldier*);
	void SetTargetController();
	static cocos2d::Vector<Soldier*> _beChoosed;

private:

	
	cocos2d::Point _getTouchBeganPos;
	cocos2d::Point _getTouchEndedPos;

	cocos2d::Sprite* _selectBox;
	

	//===========by lym===============
private:
	static cocos2d::Vector<Soldier*> _soldierVec;
	static cocos2d::Vector<Soldier*> _dogVec;
	static cocos2d::Vector<Soldier*> _infantryVec;
	static cocos2d::Vector<Soldier*> _tankVec;
public:
	static Soldier *CreateSoldier(char* SoldierTypeName);
};