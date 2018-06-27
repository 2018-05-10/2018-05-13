#include"LoadingScene.h"
#include"SimpleAudioEngine.h"
#include"GameScene\GameScene.h"
#include"MenuScene.h"
#include"Tool/AnimationTool.h"
USING_NS_CC;

using namespace CocosDenshion;

Scene* LoadingScene::createScene()
{
	auto _scene = Scene::create();
	auto _layer = LoadingScene::create();
	_scene->addChild(_layer);

	return _scene;
}

bool LoadingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto loadingBar = createLoadingBar();
	this->addChild(loadingBar);
	auto func1 = [=]()
	{
		LoadSpriteFrame();
		loadingBar->setPercent(40);
	};
	auto callFunc1 = CallFunc::create(func1);
	auto func2 = [=]()
	{
		LoadImage();
		loadingBar->setPercent(70);
	};
	auto callFunc2 = CallFunc::create(func2);
	auto func3 = [=]()
	{
		LoadSound();
		loadingBar->setPercent(100);
	};
	auto callFunc3 = CallFunc::create(func3);
	auto func4 = [=]()
	{
		endLoading();
	};
	auto callFunc4 = CallFunc::create(func4);

	this->runAction(Sequence::create(callFunc1, callFunc2, callFunc3, callFunc4, NULL));

	return true;
}

void LoadingScene::LoadSound()
{
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("backgroundmusic.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/ClickSound.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/BoomSound.wav");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Attack.wav");
}

void LoadingScene::endLoading()
{
	const auto transition = TransitionFade::create(1,MenuScene::createScene());
	Director::getInstance()->replaceScene(transition);
}
void LoadingScene::LoadImage()
{
	auto cache = TextureCache::getInstance();
	cache->addImage("dogpicture.png");
	cache->addImage("soldierpicture.png");
	cache->addImage("tankpicture.png");
	cache->addImage("bg.png");
	cache->addImage("selectbox.png");
	cache->addImage("button.png");
	cache->addImage("buttonHighlighted.png");
	GameScene::_frameCache->addSpriteFramesWithFile("Entity/Explosion.plist", "Entity/Explosion.png");
	AnimationTool::getInstance()->loadAnimation();
}
void LoadingScene::LoadSpriteFrame()
{
	GameScene::_frameCache->addSpriteFramesWithFile("material.plist", "material.png");
}

cocos2d::ui::LoadingBar* LoadingScene::createLoadingBar() {
	const auto visibleSize = Director::getInstance()->getVisibleSize();
	const auto baseY = visibleSize.height * 0.35f;

	auto loadingBar = ui::LoadingBar::create("loading bar.jpg");
	loadingBar->setPosition(Vec2(visibleSize.width / 2, baseY));
	loadingBar->setScale(0.5);
	loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
	loadingBar->setPercent(10);

	return loadingBar;
}