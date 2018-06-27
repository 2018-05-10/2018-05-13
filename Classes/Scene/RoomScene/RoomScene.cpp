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
	initNameLayer();

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
				if (Player::getInstance()->serve->IsConnected()&& Player::getInstance()->client->_isReady)
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
		readyButton->addTouchEventListener([&, readyButton](Ref*, Widget::TouchEventType type)
		{
			switch (type)
			{
			case Widget::TouchEventType::BEGAN:
				CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ClickSound.wav");
				break;
			case Widget::TouchEventType::MOVED:
				break;
			case Widget::TouchEventType::ENDED:
				if (!Player::getInstance()->client->_isReady)
				{
					Player::getInstance()->client->_isReady = 1;
					Player::getInstance()->client->_chatMsgSend.push_back("_getReady");
					readyButton->setTitleText("Cancel");
				}
				else
				{
					Player::getInstance()->client->_isReady = 0;
					Player::getInstance()->client->_chatMsgSend.push_back("_cancelReady");
					readyButton->setTitleText("Ready");
				}
				break;
			}
		});
	}

	auto layer = LayerColor::create(Color4B::WHITE);
	layer->setOpacity(150);
	layer->setContentSize(Size(visibleSize.width/6, visibleSize.height));
	this->addChild(layer);
	auto chatBox = ChatBox::create();
	chatBox->setPosition(visibleSize.width * 0.08f, visibleSize.height * 0.15f);
	layer->addChild(chatBox);
	this->scheduleUpdate();

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
	 if (Player::getInstance()->isMaster)
	 {
		 if (Player::getInstance()->client->_opponentName != "" && _clientName==nullptr)
		 {
			 auto size = clientLayer->getContentSize();
			 _clientName = ui::Text::create(Player::getInstance()->client->_opponentName, "fonts/OpenSans-Regular.ttf", Setting::Font::Size::normal);
			 _clientName->setColor(Color3B::BLUE);
			 clientLayer->addChild(_clientName);
			 _clientName->setPosition(size / 2);
		 }
	 }
	 else
	 {
		 if (Player::getInstance()->client->_opponentName != "" && _masterName == nullptr)
		 {
			 auto size = masterLayer->getContentSize();
			 _masterName = ui::Text::create(Player::getInstance()->client->_opponentName, "fonts/OpenSans-Regular.ttf", Setting::Font::Size::normal);
			 _masterName->setColor(Color3B::RED);
			 masterLayer->addChild(_masterName);
			 _masterName->setPosition(size / 2);
		 }
	 }

}

 void RoomScene::initNameLayer()
 {
	 auto visibleSize = Director::getInstance()->getVisibleSize();

	 masterLayer = LayerColor::create(Color4B::WHITE);
	 clientLayer = LayerColor::create(Color4B::WHITE);
	 masterLayer->setContentSize(visibleSize / 5);
	 clientLayer->setContentSize(visibleSize / 5);
	 masterLayer->setOpacity(150);
	 clientLayer->setOpacity(150);
	 this->addChild(masterLayer);
	 this->addChild(clientLayer);
	 masterLayer->setPosition(visibleSize.width * 1 / 5, visibleSize.height * 3 / 4);
	 clientLayer->setPosition(visibleSize.width * 3 / 5, visibleSize.height * 3 / 4);
	 if (Player::getInstance()->isMaster)
	 {
		 auto size = masterLayer->getContentSize();
		 _masterName = ui::Text::create(Player::getInstance()->getName(),"fonts/OpenSans-Regular.ttf", Setting::Font::Size::normal);
		 _masterName->setColor(Color3B::RED);
		 masterLayer->addChild(_masterName);
		 _masterName->setPosition(size / 2);
	 }
	 else
	 {
		 auto size = clientLayer->getContentSize();
		 _clientName = ui::Text::create(Player::getInstance()->getName(), "fonts/OpenSans-Regular.ttf", Setting::Font::Size::normal);
		 _clientName->setColor(Color3B::BLUE);
		 clientLayer->addChild(_clientName);
		 _clientName->setPosition(size / 2);
	 }
 }