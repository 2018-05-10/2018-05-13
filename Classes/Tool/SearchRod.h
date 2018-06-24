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
		int f;//g+h  我们的参考值
		int g;//起点到当前点的消耗   
		int h;//终点到当前点的理论消耗   
		JieDian* parent;//前一步的节点
		JieDian(int ix, int iy) //当前节点记为ix和iy
		{
			x = ix;
			y = iy;
			f = 0;
			g = 0;
			h = 0;
			parent = NULL;
		}
		JieDian(int ix, int iy, JieDian* snd_parent) //后面的父节点
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

	 std::vector<JieDian*> openList;//可走的地方
	 std::vector<JieDian*> closeList;//不可走的地方
	 int row = 100;//地图总行数   
	 int col = 100;//地图总列数   
	 JieDian* startPos;//开始点   
	 JieDian* endPos;//结束点   
	 int pingyi = 10;//平移权重   
	 int xieyi = 14;//斜移权重   
}