/*
    �ļ�����    FlowWord.h
    �衡����    ����Ʈ��Ч��
    �����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)
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