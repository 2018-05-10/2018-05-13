#include "FlowWord.h"

bool FlowWord::init() 
{
	m_textLab = Label::create("", "Arial", 30);
	m_textLab->setColor(Color3B(255, 0, 0));
	m_textLab->setAnchorPoint(Point(1, 0));
	m_textLab->setVisible(false);

	this->addChild(m_textLab);
	return true;
}

void FlowWord::showWord( std::string text, Point pos, float dur, float size)
{
	m_textLab->setString(text);
	m_textLab->setPosition(pos);
	m_textLab->setVisible(true);

	/* 组合两个动作，放大后缩小 */
    auto scaleLarge = ScaleTo::create(dur,size, size);

    auto callFunc = CallFunc::create([&](){
        /* 动作结束，从父节点中删除自身 */
        m_textLab->setVisible(false);
        m_textLab->removeFromParentAndCleanup(true);
    });

    auto actions = Sequence::create(scaleLarge, callFunc, NULL);

	m_textLab->runAction(actions);
}


