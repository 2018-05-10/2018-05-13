#include"RoomScene.h"
#include"ChatBox.h"
#include"ui/CocosGUI.h"
#include"Entity/Player.h"
#include"SimpleAudioEngine.h"
#include"Scene/GameScene/GameScene.h"
#include"Setting.h"
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


	if (Player::getInstance()->isMaster)
	{
		auto startButton = CreateButton("Start");
		startButton->setTitleFontSize(Setting::Font::Size::normal);
		this->addChild(startButton);
		startButton->addTouchEventListener([&, startButton](Ref*, Widget::TouchEventType type)
		{
			switch (type)
			{
			case Widget::TouchEventType::BEGAN:
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ClickSound.wav");
				break;
			case Widget::TouchEventType::MOVED:
				break;
			case Widget::TouchEventType::ENDED:
				if (Player::getInstance()->serve->IsConnected())
				{
					SendStep(Player::getInstance()->serve);
					auto transition = TransitionFade::create(0.5, GameScene::createScene());
					Director::getInstance()->replaceScene(transition);
				}
				break;
			}
		});
	}
	else
	{
		auto readyButton = CreateButton("Ready");
		readyButton->setTitleFontSize(Setting::Font::Size::normal);
		this->addChild(readyButton);
	}

	auto layer = LayerColor::create(Color4B::WHITE);
	layer->setOpacity(150);
	layer->setContentSize(Size(visibleSize.width/6, visibleSize.height));
	this->addChild(layer);
	auto chatBox = ChatBox::create();
	chatBox->setPosition(visibleSize.width * 0.08f, visibleSize.height * 0.15f);
	layer->addChild(chatBox);
	this->scheduleUpdate();

	auto text = Text::create(Player::getInstance()->client->_opponentName, "fonts/OpenSans-Regular.ttf", 24);
	this->addChild(text);
	text->setPosition(Point(900, 400));

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

 void RoomScene::update(float dt)
{
	 if (Player::getInstance()->client->_step >=2)
	 {
		 auto transition = TransitionFade::create(0.5, GameScene::createScene());
		 Director::getInstance()->replaceScene(transition);
		 this->unscheduleUpdate();
	 }
	 auto tmp = Player::getInstance()->client->_opponentName;

}