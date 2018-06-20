/*
    文件名：    FlowWord.h
    描　述：    文字飘动效果
    创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)
*/

#ifndef _FlowWord_H_
#define _FlowWord_H_

#include "cocos2d.h"
#include<string>
USING_NS_CC;

class FlowWord : public Node {
public:
    CREATE_FUNC(FlowWord);
    virtual bool init();

public:
	void showWord(std::string text, Point pos,float dur,float size);
private:
	Label* m_textLab;
};

#endif