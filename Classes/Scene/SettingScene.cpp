#include"SettingScene.h"
#include"extensions/cocos-ext.h"
#include"SimpleAudioEngine.h"
#include"ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace extension;

Scene* SettingScene::createScene() 
{
	auto scene = Scene::create();
	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;
}


bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	BGinit();

	auto music_text = Label::createWithTTF("MusicSound", "fonts/Marker Felt.ttf", 32);
	music_text->setPosition(Vec2(visibleSize.width*0.25 + origin.x, origin.y + visibleSize.height*0.7));
	this->addChild(music_text);

	this->CreateSlider();
	this->CreateMusicButton();


	return true;
}

void SettingScene::BGinit()
{
	auto _visibleSize = Director::getInstance()->getVisibleSize();
	auto _visibleOrigin = Director::getInstance()->getVisibleOrigin();


	auto _bg = Scale9Sprite::create("bg.jpg");
	this->addChild(_bg);
	_bg->setContentSize(Size(_visibleSize.width, _visibleSize.height));
	_bg->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
}

ControlButton* SettingScene::CreateButton(std::string title, int site)
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

void SettingScene::CreateSlider()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
 
	auto sl = Slider::create();
	sl->loadBarTexture("sliderTrack.png");
	sl->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "");

	sl->loadProgressBarTexture("sliderProgress.png");
	sl->setPosition(Point(visibleOrigin.x + visibleSize.width*0.6,visibleOrigin.y + visibleSize.height*0.7));
	sl->setPercent(75);

	sl->addEventListener(CC_CALLBACK_2(SettingScene::SliderCallBack, this));
	this->addChild(sl);
}

void SettingScene::SliderCallBack(Ref *pSender, Slider::EventType type) {
	auto item = static_cast<Slider*>(pSender);
	log("%i", item->getPercent());
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(item->getPercent() / 100.0f);
}

void SettingScene::CreateMusicButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto visibleOrigin = Director::getInstance()->getVisibleOrigin();

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("backgroundmusic.mp3", true);
	auto music_button = MenuItemImage::create("music.png", "nomusic.png");
	auto pause_button = MenuItemImage::create("nomusic.png", "music.png");

	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::MenuMusicCallBack, this), music_button, pause_button, NULL);
	toggleItem->setScale(1.0f);
	toggleItem->setPosition(Point(visibleOrigin.x + visibleSize.width * 0.9, visibleOrigin.y + visibleSize.height * 0.1));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
}

void SettingScene::MenuMusicCallBack(cocos2d::Ref* pSender)
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