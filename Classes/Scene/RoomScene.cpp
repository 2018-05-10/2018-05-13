#include"RoomScene.h"
#include"ChatBox.h"
#include"ui\CocosGUI.h"
#include"Entity\Player.h"
#include"SimpleAudioEngine.h"
#include"GameScene\GameScene.h"

USING_NS_CC;
using namespace ui;

Scene* RoomScene::createScene()
{
	auto scene = Scene::create();

	auto layer = RoomScene::create();

	scene->addChild(layer);

	return scene;
}
bool RoomScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	BGinit();

	if (Player::getInstance()->isMaster)
	{
		RecvAndSend(Player::getInstance()->serve);
	}
	SendMsgMod(Player::getInstance()->client);
	RecvMsgMod(Player::getInstance()->client);

	auto startButton = CreateButton("Start");
	this->addChild(startButton);
	startButton->addTouchEventListener([&,startButton](Ref*, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ClickSound.wav");
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
			if (!Player::getInstance()->isMaster)
			{
				return;
			}
			if (Player::getInstance()->serve->IsConnected())
			{
				auto transition = TransitionFade::create(0.5, GameScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
			break;
		}
	});


	auto layer = LayerColor::create(Color4B::WHITE);
	layer->setOpacity(150);
	layer->setContentSize(Size(visibleSize.width/4, visibleSize.height));
	this->addChild(layer);
	auto chatBox = ChatBox::create();
	chatBox->setPosition(visibleSize.width * 0.08f, visibleSize.height * 0.15f);
	layer->addChild(chatBox);
	return true;
}

void RoomScene::BGinit()
{
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	auto _visibleOrigin = Director::getInstance()->getVisibleOrigin();


	auto _bg = Scale9Sprite::create("bg.png");
	this->addChild(_bg);
	_bg->setContentSize(Size(_visibleSize.width, _visibleSize.height));
	_bg->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
}

Button* RoomScene::CreateButton(std::string title)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto button = Button::create("button.png", "buttonHighlighted.png");
	button->setScale9Enabled(true);
	button->setSize(Size(300, 50));
	button->setTitleText(title);
	button->setTitleFontSize(20);
	button->setPosition(Vec2(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.x + visibleSize.height / 6));

	return button;
}