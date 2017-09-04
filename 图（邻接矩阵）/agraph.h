//AGraph.h图抽象类的定义
#ifndef _AGRAPH_H_
#define _AGRAPH_H_
#define big 10000000
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef int VRType;//定义顶点关系（权值）类型为整形
template<typename VerT>class AGraph
{
private:
		void DFS(int i, void(*visit)(VerT), bool Visited[])
	{//从顶点[i]出发递归的深度优先遍历图，DFSTraverse()调用
		Visited[i] = true;//设置访问标志为true（已访问）
		visit(GetVex(i));//访问顶点[i]
		for (int j = FirstAdjVex(i); j >= 0; j = NextAdjVex(i, j))
			//从顶点[i]的第一个邻接顶点[j]开始
			if (!Visited[j])//邻接顶点[j]未被访问
				DFS(j, visit, Visited);
		//对顶点[i]的尚未访问的邻接顶点[j]递归调用DFS
	}
protected:
	int ArcNum;//图的弧数
	bool Weight=0;//ture：带权；false：无权
	bool Directed=0;//ture：有向；false：无向
public:
	void CreateFromFile(char* FileName);//由数据文件FileName创建图
	void InsertVex(VerT v);//增添新顶点v
	bool DeleteVex(VerT v);//删除定点v及其相关的弧
	bool InsertArc(VerT v,VerT w);//增添弧<v,w>,如果是无向的还应该添加<w,v>
	bool DeleteArc(VerT v,VerT w);//删除弧<v,w>,如果是无向的还应该删除<w,v>
	virtual int GetVexNumOrArcNum(int i)const = 0;//返回图的顶点数（i=0）或弧数（i=1）
	virtual VerT GetVex(int i)const = 0;//返回顶点[i]的值
	virtual int FirstAdjVex(int i)const = 0;
	virtual int NextAdjVex(int i, int j)const = 0;
	void DFSTraverse(void(*visit)(VerT))
	{//从顶点[0]起，深度优先递归遍历图，并对每个顶点调用函数visit一次且仅一次
		int i;
		bool *Visited = new bool[GetVexNumOrArcNum(0)];
		for (i = 0; i<GetVexNumOrArcNum(0); i++)
			Visited[i] = false;
		for (i = 0; i<GetVexNumOrArcNum(0); i++)
			if (!Visited[i])
				DFS(i, visit, Visited);
		cout << endl;
		delete[]Visited;
	}
};

#endif