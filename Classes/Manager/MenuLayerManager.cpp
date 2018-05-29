#include"MenuLayerManager.h"

USING_NS_CC;

bool MenuLayerManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	_menuLayer = MenuLayer::create();
	this->addChild(_menuLayer);
}

void MenuLayerManager::SetBuildingController(Sprite* building,Scene* scene)
{
	auto listener1 = EventListenerTouchOneByOne::create();
	     listener1->setSwallowTouches(true);
	auto target = Sprite::createWithSpriteFrame(building->getSpriteFrame());
	target->setPosition(building->getPosition());
	scene->addChild(target);
		    //ͨ�� lambda ���ʽ ֱ��ʵ�ִ����¼��Ļص�����
	listener1->onTouchBegan = [&](Touch* touch, Event* event)
	{
		
			  Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		      Size s = target->getContentSize();
		      Rect rect = Rect(0, 0, s.width, s.height);
		
			  if (rect.containsPoint(locationInNode))
			         {
			            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			            target->setOpacity(180);//�����ʱ������ɫ�䰵��255Ϊ���ֵ��0��С
			             return true;
			         }
		         return false;
		     };
		
		     listener1->onTouchMoved = [=](Touch* touch, Event* event) {
		       
		         target->setPosition(target->getPosition() + touch->getDelta());
		     };
	
		     listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		        log("sprite onTouchesEnded.. ");
		        target->setOpacity(255);//�����ɿ�ʱʹ����ָ�ԭ������ɫ
		     };
	
		
		     //�������¼��󶨵���������
		     _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, building);
}

MenuLayer* MenuLayerManager::getMenuLayer() const
{
	return _menuLayer;
}