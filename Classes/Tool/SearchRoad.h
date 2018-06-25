#pragma once
#include"cocos2d.h"
class Soldier;
namespace SearchRoad
{
	class Node
	{
	public:
		int x;
		int y;
		int f;//g+h  我们的参考值
		int g;//起点到当前点的消耗   
		int h;//终点到当前点的理论消耗   
		Node* parent;//前一步的节点
		Node(int ix, int iy) //当前节点记为ix和iy
		{
			x = ix;
			y = iy;
			f = 0;
			g = 0;
			h = 0;
			parent = NULL;
		}
		Node(int ix, int iy, Node* snd_parent) //后面的父节点
		{
			x = ix;
			y = iy;
			f = 0;
			g = 0;
			h = 0;
			parent = snd_parent;
		}
	};

	 int countH(Node* sNode, Node* eNode);
	 void countFGH(Node* sNode, Node* eNode, int cost);
	 int Contains(std::vector<Node*>& v, int x, int y);
	 void checkMove(int x, int y, Node* parent, Node* end, int cost);
	 void releaseNode(Node* n, Soldier* soldier);
	 int startSearch(cocos2d::Point start, cocos2d::Point end, Soldier*);

	 std::vector<Node*> openList;//可走的地方
	 std::vector<Node*> closeList;//不可走的地方
	 int row = 100;//地图总行数   
	 int col = 100;//地图总列数   
	 Node* startPos;//开始点   
	 Node* endPos;//结束点   
	 int pingyi = 10;//平移权重   
	 int xieyi = 14;//斜移权重   
}