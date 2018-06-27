#include "ChatBox.h"
#include"Entity/Player.h"
#include"Setting.h"
USING_NS_CC;

constexpr int MAX_MSG_NUM = 10;

bool ChatBox::init()
{

	if (!Node::init())
	{
		return false;
	}
	boxInputInit();
	boxHistoryInit();

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(ChatBox::keyReleasedAct, this);



	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	this->schedule(schedule_selector(ChatBox::updateHistory), 0.5f);

	return true;
}

void ChatBox::keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	switch (keycode) {
	case EventKeyboard::KeyCode::KEY_ENTER:
		if (isInputing) {
			static_cast<TextFieldTTF*>(boxInput->getVirtualRenderer())->detachWithIME();
			if (!boxInput->getString().empty()) {
				Player::getInstance()->client->_chatMsgSend.push_back(boxInput->getString());
				auto str = Player::getInstance()->getName()+std::string(": ")+ boxInput->getString();
				auto text = cocos2d::ui::Text::create(str, "fonts/OpenSans-Regular.ttf", Setting::Font::Size::chat);
				text->ignoreContentAdaptWithSize(false);
				text->setColor(cocos2d::Color3B::RED);
				auto width = text->getContentSize().width;
				text->setContentSize(Size(400, 26 * (1 + (width + 60) / 400)));
				boxHistory->addChild(text, 0);
				if (boxHistory->getChildrenCount() > MAX_MSG_NUM)
					boxHistory->removeItem(0);
				boxInput->setString("");
				
			}
			isInputing = false;
		}
		else {
			boxInput->attachWithIME();
			isInputing = true;
		}
	}
}

void ChatBox::boxInputInit()
{
	boxInput = cocos2d::ui::TextField::create("Chat Here",
		"fonts/OpenSans-Regular.ttf",24);
	boxInput->setTextColor(Color4B(0, 0, 0, 255 * 0.9f));
	boxInput->setCursorEnabled(true);
	boxInput->setCursorChar('|');
	boxInput->setMaxLength(50);
	boxInput->setMaxLengthEnabled(true);
	this->addChild(boxInput);
}

void ChatBox::boxHistoryInit()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	boxHistory = cocos2d::ui::ListView::create();
	boxHistory->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
	boxHistory->setContentSize(Size(200,150));
	boxHistory->setBackGroundColor(Color3B(50, 50, 50));
	boxHistory->setBackGroundColorOpacity(225 * 0.8f);
	boxHistory->setPosition(Point(-50, 0));

	addChild(boxHistory);
}

void ChatBox::InputStart()
{
}

void ChatBox::InputFinish()
{
}

void ChatBox::updateHistory(float dt)
{
	

	for (auto txt : Player::getInstance()->client->_chatMsgRecv)
	{
		auto str = Player::getInstance()->client->_opponentName + std::string(": ") + txt;
		auto text = cocos2d::ui::Text::create(str, "fonts/OpenSans-Regular.ttf", Setting::Font::Size::chat);
		text->ignoreContentAdaptWithSize(false);
		text->setColor(cocos2d::Color3B::BLUE);
		auto width = text->getContentSize().width;
		text->setContentSize(Size(400, 26 * (1 + (width + 60) / 400)));
		boxHistory->addChild(text, 0);
		if (boxHistory->getChildrenCount() > MAX_MSG_NUM)
			boxHistory->removeItem(0);
	}
	Sleep(10);
	Player::getInstance()->client->_chatMsgRecv.clear();
	boxHistory->forceDoLayout();
	boxHistory->jumpToBottom();
}

void ChatBox::initChatBox()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_chatBoxBG = Sprite::create("input_normal.png");
	_chatBoxBG->setScale(1.2f);
	_chatBoxBG->setOpacity(200);



	_chatBoxBG->setScale(1.5);

	this->addChild(_chatBoxBG);

}