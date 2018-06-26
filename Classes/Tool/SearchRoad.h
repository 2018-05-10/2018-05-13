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
		int f;//g+h  ���ǵĲο�ֵ
		int g;//��㵽��ǰ�������   
		int h;//�յ㵽��ǰ�����������   
		Node* parent;//ǰһ���Ľڵ�
		Node(int ix, int iy) //��ǰ�ڵ��Ϊix��iy
		{
			x = ix;
			y = iy;
			f = 0;
			g = 0;
			h = 0;
			parent = NULL;
		}
		Node(int ix, int iy, Node* snd_parent) //����ĸ��ڵ�
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

	 std::vector<Node*> openList;//���ߵĵط�
	 std::vector<Node*> closeList;//�����ߵĵط�
	 int row = 100;//��ͼ������   
	 int col = 100;//��ͼ������   
	 Node* startPos;//��ʼ��   
	 Node* endPos;//������   
	 int pingyi = 10;//ƽ��Ȩ��   
	 int xieyi = 14;//б��Ȩ��   
}