#ifndef _BHC_H_
#define _BHC_H_

template<typename VerT, typename ArcT>
class BHC
{
	int **DD;//分配M个最短距离表
	int ***PP;
public:
	BHC()
	{
		DD = new int*[M];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
			DD[i] = new int[MAX_VERTEX_NUM]();//后面的()能将开辟的动态数组初始化为0。

		PP = new int**[M];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			PP[i] = new int*[MAX_VERTEX_NUM];
			for (int j = 0; j <MAX_VERTEX_NUM; j++)
			{
				PP[i][j] = new int[MAX_VERTEX_NUM]();
			}
		}
	}
	~BHC()
	{
		//删除相关的动态数组
		for (int i = 0; i < M; i++)
		{
			delete[]DD[i];
		}
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j <MAX_VERTEX_NUM; j++)
			{
				delete[]PP[i][j];
			}
		}
	}
	int NearHostCmax(MatrixGraph<VerT, ArcT> &G, ShortestPath<VerT, ArcT> &PATH)
	{
		for (int i = 0; i < M; i++)
		{
			PATH.ShortestPath_DIJ(G, G.host[i].name);
			for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
			{
				DD[i][j] = PATH.D[j];
				for (int k = 0; k < G.GetVexNumOrArcNum(0); k++)
				{
					PP[i][j][k] = PATH.P[j][k];
				}
			}
		}
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			PATH.C[i] = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			int TESTDD = DD[0][i];
			int NUMDD = 0;
			for (int j = 0; j < M; j++)
			{//得出第i个顶点离哪个主机最近
				if (DD[j][i] < TESTDD)
				{
					TESTDD = DD[j][i];
					NUMDD = j;
				}
			}
			cout << "df" << NUMDD;
			for (int m = 0; m < G.GetVexNumOrArcNum(0); m++)
			{
				cout << PP[i][NUMDD][m];
				if (m != i&&m != NUMDD)
					PATH.C[m] = PATH.C[m] + PP[i][NUMDD][m];//第i顶点到最近的j点通过的点
			}
		}
		int v;//最大使用率的第v个顶点
		int total = 0;
		int max = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			total += PATH.C[i];
			if (max < PATH.C[i])
			{
				max = PATH.C[i];
				v = i;
			}
		}
		cout << "图中最大节点使用概率和次数：" << (float)max / total << "  " << max << endl;
		cout << "最大使用率节点和其度数:" << v << "  " << G.ReturnDeg(v) << endl;
		return max;
	}
	
};
#endif