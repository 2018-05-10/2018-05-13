#pragma once
#include"cocos2d.h"
#include "ui/UITextField.h"
#include "ui/UIText.h"
#include "ui/UIListView.h"

class ChatBox :public cocos2d::Layer {
public:
	virtual bool init();

	void keyReleasedAct(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* event);
	std::function<void(const std::string&)> sendText;

	CREATE_FUNC(ChatBox);
private:
	cocos2d::ui::ListView *boxHistory;
	cocos2d::ui::TextField *boxInput;
	cocos2d::Sprite* _chatBoxBG;

	void initChatBox();
	void boxInputInit();
	void boxHistoryInit();
	void InputStart();
	void InputFinish();
	bool isInputing = false;
	void updateHistory(float dt);
};