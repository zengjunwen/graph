#ifndef _BETWEENNESS_H_
#define _BETWEENNESS_H_
#include<stack>
#include<queue>
using namespace std;
int MyCompareOrderB(const void * elem1, const void * elem2)
{//排序函数中的比较函数定义
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p2 - *p1);
}
template<typename VerT, typename ArcT>class Betweenness
{
private:
	float *B = new float[MAX_VERTEX_NUM];
	float *OrderB = new float[MAX_VERTEX_NUM];
public:
	Betweenness()
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			B[i] = 0;
			OrderB[i] = 0;
		}
	}
	~Betweenness()
	{
		delete[]B;
		delete[]OrderB;
		cout << "删除中心性动态数组和其排序数组！" << endl;
	}
	void CountB(MatrixGraph<VerT, ArcT>&G)
	{
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{//对于所有顶点s属于顶点V进行操作
			stack<int> S;
			int **P;
			P = new int*[G.GetVexNumOrArcNum(0)];
			for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			{
				P[i] = new int[G.GetVexNumOrArcNum(0)];
			}
			for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			{
				for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
				{
					P[i][j] = 0;
				}
			}
			int *C = new int[G.GetVexNumOrArcNum(0)];
			for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			{
				C[i] = 0;
			}
			C[i] = 1;
			int *d = new int[G.GetVexNumOrArcNum(0)];
			for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			{
				d[i] = -1;
			}
			d[i] = 0;
			queue<int> Q;
			Q.push(i);
			while (Q.size() != 0)
			{
				int v = Q.front();
				Q.pop();
				S.push(v);
				for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
				{
					if (G.Getarcs(v,j) == 1)
					{//for each neighbor w of v
						if (d[j] < 0)
						{
							Q.push(j);
							d[j] = d[v] + 1;
						}
						if (d[j] == (d[v] + 1))
						{
							C[j] = C[j] + C[v];
							P[j][v] = 1;
						}
					}
				}
			}
			float *Delta = new float[G.GetVexNumOrArcNum(0)];
			for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			{
				Delta[i] = 0;
			}
			while (S.size() != 0)
			{
				int w = S.top();
				S.pop();
				for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
				{
					if (P[w][i] == 1)
					{
						Delta[i] = Delta[i] + (float)C[i] / C[w] * (1 + Delta[w]);
					}
				}
				if (w != i)
					B[w] = B[w] + Delta[w];
			}
			delete[]C;
			delete[]d;
		}
	}
	void ShowB(int i)
	{
		cout << "第" << i << "个节点的接近中心性为：" << B[i] << endl;
	}
	float ReturnB(int i)
	{
		return B[i];
	}
	void OrderBigToSmallB(MatrixGraph<VerT, ArcT>&G)
	{
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{//将CC[]复制到OrderCC[]中
			OrderB[i] = B[i];
		}
		qsort(OrderB, G.GetVexNumOrArcNum(0), sizeof(float), MyCompareOrderB);
	}
	float ReturnOrderB(int i)
	{
		return OrderB[i];
	}
	void ShowOrderB(int i)
	{
		cout << "OrderB[]中元素" << i << "的中心性为：" << OrderB[i] << endl;
	}
};
#endif