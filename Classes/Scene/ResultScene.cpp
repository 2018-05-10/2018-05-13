#include"ResultScene.h"
#include"ui/CocosGUI.h"
#include"Entity/Player.h"
#include"Setting.h"
#include"MenuScene.h"
#include"SimpleAudioEngine.h"
USING_NS_CC;
using namespace ui;

Scene* ResultScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ResultScene::create();
	scene->addChild(layer);
	return scene;
}

bool ResultScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	BGinit();
	if (Player::getInstance()->getResult())
	{
		auto label = Label::createWithTTF("You WIN", Setting::Font::Type::title, Setting::Font::Size::title);
		label->setColor(Color3B::YELLOW);
		this->addChild(label);
		label->setPosition(visibleSize / 2);
	}
	else
	{
		auto label = Label::createWithTTF("You LOSE", Setting::Font::Type::title, Setting::Font::Size::title);
		label->setColor(Color3B::BLUE);
		this->addChild(label);
		label->setPosition(visibleSize / 2);
	}

	this->scheduleOnce(schedule_selector(ResultScene::update), 1.0f);

	return true;
}

void ResultScene::BGinit()
{
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	auto _visibleOrigin = Director::getInstance()->getVisibleOrigin();


	auto _bg = Scale9Sprite::create("bg.png");
	this->addChild(_bg);
	_bg->setContentSize(Size(_visibleSize.width, _visibleSize.height));
	_bg->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
}
void ResultScene::update(float dt)
{
	if (!Player::getInstance()->isMaster)
	{
		delete Player::getInstance()->client;
	}

	if (Player::getInstance()->isMaster)
	{
		delete Player::getInstance()->client;
		delete Player::getInstance()->serve;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto button = Button::create("button.png", "buttonHighlighted.png");
	button->setScale9Enabled(true);
	button->setSize(Size(300, 50));
	button->setTitleText("Return");
	button->setTitleFontSize(20);
	button->setPosition(Vec2(visibleOrigin.x + visibleSize.width / 2, visibleOrigin.y + visibleSize.height / 4));
	this->addChild(button);
	button->addTouchEventListener([&](Ref*, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/ClickSound.wav");
			break;
		case Widget::TouchEventType::MOVED:
			break;
		case Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
			break;
		}
	});
}