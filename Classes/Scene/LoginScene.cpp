#include"LoginScene.h"
#include"NetScene.h"
#include"SimpleAudioEngine.h"
#include"Entity\Player.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

Scene* LoginScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoginScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoginScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	BGinit();
	createLoginButton();

	initPlayerBox();

	return true;
}

void LoginScene::BGinit()
{
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	auto _visibleOrigin = Director::getInstance()->getVisibleOrigin();


	auto _bg = Scale9Sprite::create("bg.png");
	this->addChild(_bg);
	_bg->setContentSize(Size(_visibleSize.width, _visibleSize.height));
	_bg->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
}

void LoginScene::createLoginButton()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto loginButton = Button::create("button.png", "buttonHighlighted.png");
	loginButton->setScale9Enabled(true);
	loginButton->setSize(Size(300, 50));
	loginButton->setTitleText("Login");
	loginButton->setTitleFontSize(32);
	loginButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.35f));
	loginButton->setOpacity(233);

	loginButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED)
		{

			return;
		}
		SimpleAudioEngine::sharedEngine()->playEffect("Sound/ClickSound.wav");
		std::string username = PlayernameInput->getString();
		if (username.empty())
		{
			MessageBox("Playername can't be empty", "Alert");
		}
		else
		{
			username.substr(0, 16);
			Player::getInstance()->setName(username);
			Player::getInstance()->client->_playerName;
		
			Director::getInstance()->replaceScene(TransitionFade::create(1.2f, NetScene::createScene()));
		}
	});
	addChild(loginButton);
}

void LoginScene::initPlayerBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	PlayernameBG = Sprite::create("input_normal.png");
	PlayernameBG->setScale(1.2f);
	PlayernameBG->setOpacity(200);

	PlayernameInput = ui::TextField::create("Input Playername Here", "fonts/Quicksand-Bold.ttf", 20);
	PlayernameInput->setColor(Color3B::BLACK);
	PlayernameInput->setCursorChar('|');
	PlayernameInput->setCursorEnabled(true);
	PlayernameInput->setMaxLength(15);
	PlayernameInput->setMaxLengthEnabled(true);
	PlayernameInput->setPosition(PlayernameBG->getContentSize() / 2);
	PlayernameInput->addEventListener(CC_CALLBACK_2(LoginScene::textFieldEvent, this));

	PlayernameBG->addChild(PlayernameInput);

	PlayernameBG->setScale(1.5);
	PlayernameBG->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2 + PlayernameBG->getContentSize().height * 2));

	addChild(PlayernameBG);

}

void LoginScene::textFieldEvent(Ref* sender, ui::TextField::EventType event)
{
	switch (event) {
	case ui::TextField::EventType::ATTACH_WITH_IME:
		PlayernameBG->setTexture("input_active.png");
		break;
	case ui::TextField::EventType::DETACH_WITH_IME:
		PlayernameBG->setTexture("input_normal.png");
		break;
	}
}