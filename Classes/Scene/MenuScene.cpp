#include"MenuScene.h"
#include"SettingScene.h"
#include"SimpleAudioEngine.h"
#include"extensions/cocos-ext.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
using namespace extension;
using namespace ui;

Scene* MenuScene::createScene()
{
	auto _scene = Scene::create();
	auto _layer = MenuScene::create();
	_scene->addChild(_layer);

	return _scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	

	//设置背景图片
	BGinit();

	//开始按钮
	auto _startControlBtn=CreateButton("Start",3);
	this->addChild(_startControlBtn);

	//设定按钮
	auto _setControlBtn = CreateButton("Setting", 2);
	this->addChild(_setControlBtn);
	_setControlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::TouchSetting), Control::EventType::TOUCH_UP_INSIDE);
	
	//退出按钮
	auto _quitControlBtn = CreateButton("Quit", 1);
	this->addChild(_quitControlBtn);
	_quitControlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuScene::TouchQuit), Control::EventType::TOUCH_UP_INSIDE);

	auto keyEventListener = EventListenerKeyboard::create();
	keyEventListener->onKeyReleased = [](EventKeyboard::KeyCode code, Event* event)
	{
		if (code == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->end();
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyEventListener, this);

	//背景乐开关
	this->CreateMusicButton();

	return true;
}

ControlButton* MenuScene::CreateButton(std::string title, int site)
{
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	auto _visibleOrigin = Director::getInstance()->getVisibleOrigin();

	auto BtnNormal = Scale9Sprite::create("button.png");
	auto BtnDown = Scale9Sprite::create("buttonHighlighted.png");
	auto Title = Label::create(title, "Marker Felt", 30);
	auto ControlBtn = ControlButton::create(Title, BtnNormal);

	ControlBtn->setBackgroundSpriteForState(BtnDown, Control::State::HIGH_LIGHTED);
	ControlBtn->setPosition(Point(_visibleOrigin.x + _visibleSize.width / 4, _visibleOrigin.y + _visibleSize.height / 4 * site));
	ControlBtn->setPreferredSize(CCSize(300, 50));

	return ControlBtn;
}

void MenuScene::MenuMusicCallBack(cocos2d::Ref* pSender)
{

	if (_musicOn)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

		_musicOn = false;
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

		_musicOn = true;
	}
}

void MenuScene::TouchQuit(Ref* pSender, Control::EventType event)
{
	Director::getInstance()->end();


}

void MenuScene::TouchSetting(Ref* pSender, Control::EventType event)
{
		auto transition = TransitionFade::create(0.5, SettingScene::createScene());
		Director::getInstance()->pushScene(transition);
}

void MenuScene::BGinit()
{
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	auto _visibleOrigin = Director::getInstance()->getVisibleOrigin();


	auto _bg = Scale9Sprite::create("bg.jpg");
	this->addChild(_bg);
	_bg->setContentSize(Size(_visibleSize.width, _visibleSize.height));
	_bg->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
}
void MenuScene::CreateMusicButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgroundmusic.mp3", true);
	auto music_button = MenuItemImage::create("music.png", "nomusic.png");
	auto pause_button = MenuItemImage::create("nomusic.png", "music.png");

	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::MenuMusicCallBack, this), music_button, pause_button, NULL);
	toggleItem->setScale(1.0f);
	toggleItem->setPosition(Point(visibleOrigin.x + visibleSize.width * 0.9, visibleOrigin.y + visibleSize.height * 0.1));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
}