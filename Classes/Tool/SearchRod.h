#pragma once
#include"cocos2d.h"
class Soldier;
namespace SearchRoad
{
	class JieDian
	{
	public:
		int x;
		int y;
		int f;//g+h  ���ǵĲο�ֵ
		int g;//��㵽��ǰ�������   
		int h;//�յ㵽��ǰ�����������   
		JieDian* parent;//ǰһ���Ľڵ�
		JieDian(int ix, int iy) //��ǰ�ڵ��Ϊix��iy
		{
			x = ix;
			y = iy;
			f = 0;
			g = 0;
			h = 0;
			parent = NULL;
		}
		JieDian(int ix, int iy, JieDian* snd_parent) //����ĸ��ڵ�
		{
			x = ix;
			y = iy;
			f = 0;
			g = 0;
			h = 0;
			parent = snd_parent;
		}
	};

	 int countH(JieDian* sJieDian, JieDian* eJieDian);
	 void countFGH(JieDian* sJieDian, JieDian* eJieDian, int cost);
	 int Contains(std::vector<JieDian*>& v, int x, int y);
	 void checkMove(int x, int y, JieDian* parent, JieDian* end, int cost);
	 void releaseJieDian(JieDian* n, Soldier* soldier);
	 int startSearch(cocos2d::Point start, cocos2d::Point end, Soldier*);

	 std::vector<JieDian*> openList;//���ߵĵط�
	 std::vector<JieDian*> closeList;//�����ߵĵط�
	 int row = 100;//��ͼ������   
	 int col = 100;//��ͼ������   
	 JieDian* startPos;//��ʼ��   
	 JieDian* endPos;//������   
	 int pingyi = 10;//ƽ��Ȩ��   
	 int xieyi = 14;//б��Ȩ��   
}