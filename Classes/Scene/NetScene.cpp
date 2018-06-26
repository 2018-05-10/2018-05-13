#include"NetScene.h"
#include"extensions/cocos-ext.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include"RoomScene/RoomScene.h"
#include"Entity\Player.h"
#include"Entity\Soldier\Soldier.h"
#include"Entity\Building\Building.h"
USING_NS_CC;
using namespace extension;
using namespace ui;

Scene* NetScene::createScene()
{
	auto _scene = Scene::create();
	auto _layer = NetScene::create();
	_scene->addChild(_layer);

	return _scene;
}

bool NetScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	BGinit();

	auto createRoomButton = CreateButton("CreateRoom",2);
	this->addChild(createRoomButton);
	createRoomButton->addTouchEventListener([&](Ref*, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ClickSound.wav");
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
			Soldier::soldiersID=-2;
			Soldier::enemySoldiersID = -100002;
			Building::buildingsID = 2;
			Building::enemyBuildingsID = 100002;
			Player::getInstance()->serve = new Server();
			OpenTheRoom(Player::getInstance()->serve, Player::getInstance()->client,20000);
			Player::getInstance()->isMaster = true;
			auto transition = TransitionFade::create(0.5, RoomScene::createScene());
			Director::getInstance()->replaceScene(transition);
			break;
		}
	});

	auto joinRoomButton= CreateButton("JoinRoom", 1);
	this->addChild(joinRoomButton);
	joinRoomButton->addTouchEventListener([&](Ref*, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ClickSound.wav");
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
			Soldier::soldiersID = -100002;
			Soldier::enemySoldiersID = -2;
			Building::buildingsID = 1000002;
			Building::enemyBuildingsID = 2;
			RoomJoinerClient(Player::getInstance()->client, 20000);
			auto transition = TransitionFade::create(0.5, RoomScene::createScene());
			Director::getInstance()->replaceScene(transition);
			break;
		}
	});

	return true;

}

void NetScene::BGinit()
{
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	auto _visibleOrigin = Director::getInstance()->getVisibleOrigin();


	auto _bg = Scale9Sprite::create("bg.png");
	this->addChild(_bg);
	_bg->setContentSize(Size(_visibleSize.width, _visibleSize.height));
	_bg->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
}

Button* NetScene::CreateButton(std::string title, int site)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto button = Button::create("button.png", "buttonHighlighted.png");
	button->setScale9Enabled(true);
	button->setSize(Size(300, 50));
	button->setTitleText(title);
	button->setTitleFontSize(20);
	button->setPosition(Vec2(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 3 * site));

	return button;
}