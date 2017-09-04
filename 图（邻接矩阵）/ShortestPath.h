#ifndef _SHORTESTPATH_H_
#define _SHOATESTPATH_H_
template<typename VerT, typename ArcT>class  ShortestPath
{
private:
	bool **P;//路劲通过点矩阵
	bool ***ALLP;//所有路径通过点矩阵
	VRType *D = new VRType[MAX_VERTEX_NUM];//最短距离表
	int *C = new int[MAX_VERTEX_NUM]();//路径经过顶点次数
	int totalC,Cmax,AllTotalC;//alltotalC为全局节点的情况下计算的。
	int CmaxNode;
	float Umax;
	double Distance_total;
	int **PC;//连边的使用次数

	int *DD;//分配M个最短距离表

	void Path(const MatrixGraph<VerT, ArcT>&G, int v0, int v)
	{//根据ShortestPath_DIJ()所求p数组，求起始顶点v0到其余顶点v最短路劲依次通过的顶点
		bool path[MAX_VERTEX_NUM];//存放p[v]
		VRType min;//给定点到其余路径通过的点的最短距离
		int i, j = 0, k, m;//j是最短路径通过的顶点数
		for (i = 0; i < G.GetVexNumOrArcNum(0); ++i)
		{
			path[i] = P[v][i];
			if (path[i])//是最短路径上的点
				j++;
		}
		path[v0] = false;
		if (j != 0)//有最短路径
			j--;//去掉v0点
		k = v0;//由v0点起查找
		while (j>0)
		{
			min = big;
			cout << G.GetVex(k).name << "->";
			for (i = 0; i < G.GetVexNumOrArcNum(0); i++)
				if (path[i] && G.GetArc(k, i).adj < min)//顶点i是最短路径通过的点且其权值小于min
				{
					min = G.GetArc(k, i).adj;
					m = i;//顶点序号
				}
			k = m;
			path[k] = false;
			j--;
		}
		if (k != v0)
			cout << G.GetVex(k).name << endl;//输出顶点
	}
	void PathC(const MatrixGraph<VerT, ArcT>&G, int v0, int v)
	{//用于计算CP，与Path函数很像
		bool *path = new bool[MAX_VERTEX_NUM];//存放p[v]
		VRType min;//给定点到其余路径通过的点的最短距离
		int i, j = 0, k, g, m;//j是最短路径通过的顶点数
		for (i = 0; i < G.GetVexNumOrArcNum(0); ++i)
		{
			path[i] = P[v][i];
			if (path[i])//是最短路径上的点
				j++;
		}
		path[v0] = false;
		if (j != 0)//有最短路径
			j--;//去掉v0点
		g = k = v0;//由v0点起查找
		while (j>0)
		{
			min = big;
			for (i = 0; i < G.GetVexNumOrArcNum(0); i++)
				if (path[i] && G.GetArc(g, i).adj < min)//顶点i是最短路径通过的点且其权值小于min
				{
					min = G.GetArc(g, i).adj;
					m = i;//顶点序号
				}
			g = m;
			path[g] = false;
			j--;
			PC[k][g] += 1;
			k = g;
		}
		delete path;
	}
public:
	ShortestPath()
	{
		PC = new int*[MAX_VERTEX_NUM];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
			PC[i] = new int[MAX_VERTEX_NUM]();//后面的()能将开辟的动态数组初始化为0。
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
			C[i] = 0;
		totalC = 0;
		AllTotalC = 0;
		Cmax = 0;
		Umax = 0;
		CmaxNode = NULL;
		Distance_total = 0;
		P = new bool*[MAX_VERTEX_NUM];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
			P[i] = new bool[MAX_VERTEX_NUM];
		ALLP = new bool**[MAX_VERTEX_NUM];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			ALLP[i] = new bool*[MAX_VERTEX_NUM];
			for (int j = 0; j < MAX_VERTEX_NUM; j++)
				ALLP[i][j] = new bool[MAX_VERTEX_NUM];
		}
	}

	~ShortestPath()
	{
		delete[]D;
		delete[]C;
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			delete[]PC[i];
			delete[]P[i];
			for (int j = 0; j < MAX_VERTEX_NUM; j++)
				delete[]ALLP[i][j];
		}

		cout << "删除与最短路径、节点使用率相关的动态数组！" << endl;
	}
	void ShortestPath_DIJ(const MatrixGraph<VerT, ArcT>&G, int v0)
	{
		int v, w, i, j;
		VRType min;
		bool *final = new bool[MAX_VERTEX_NUM];
		for (v = 0; v < G.GetVexNumOrArcNum(0); ++v)
		{
			final[v] = false;
			D[v] = G.GetArc(v0, v).adj;
			for (w = 0; w < G.GetVexNumOrArcNum(0); ++w)
				P[v][w] = false;
			if (D[v] < big)
				P[v][v0] = P[v][v] = true;

		}
		D[v0] = 0;
		final[v0] = true;
		for (i = 1; i < G.GetVexNumOrArcNum(0); ++i)
		{
			min = big;
			for (w = 0; w < G.GetVexNumOrArcNum(0); w++)
				if (!final[w] && D[w] < min)
				{
					v = w;
					min = D[w];
				}
			final[v] = true;
			for (w = 0; w < G.GetVexNumOrArcNum(0); ++w)
				if (!final[w] && min < big && G.GetArc(v, w).adj < big && (min + G.GetArc(v, w).adj < D[w]))
				{
					D[w] = min + G.GetArc(v, w).adj;
					for (j = 0; j < G.GetVexNumOrArcNum(0); ++j)
						P[w][j] = P[v][j];
					P[w][w] = true;
				}
		}
		delete final;
	}
	void Countallshortpath(const MatrixGraph<VerT, ArcT>&G)
	{
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			ShortestPath_DIJ(G, i);
			for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
			{
				for (int k = 0; k < G.GetVexNumOrArcNum(0); k++)
					ALLP[i][j][k] = P[j][k];
			}
		}
	}
	void CoutNoedToNodeC(const MatrixGraph<VerT, ArcT>&G)
	{
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			C[i] = 0;
		}
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			for (int m = 0; m < G.GetVexNumOrArcNum(0); m++)
			{
				for (int n = 0; n<G.GetVexNumOrArcNum(0); n++)
				{
					if ((m != i) && (n != m))
						C[n] += G.ReturnGen(i)*ALLP[i][m][n];//顺便把各点的使用率计算出来
				}
			}
		}
		totalC = 0;
		Cmax = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			totalC += C[i];
			if (Cmax < C[i])
			{
				Cmax = C[i];
				CmaxNode = i;
			}
		}
		AllTotalC = totalC;
		Umax = (float)Cmax / totalC;
	}
	void show(int c)
	{
		cout << "最短距离为：";
		if (D[c]< big)
			cout << D[c];
		else
			cout << "∞";
		cout << endl;
	}
	int ReturnD(int c)
	{
		return D[c];
	}
	void AverangeDistance(MatrixGraph<VerT, ArcT> &G, int output = 0)
	{
		int T = 0;
		double Distance_total = 0;
		int local_n = G.GetVexNumOrArcNum(0);//获取图顶点数
		for (int k = 0; k < local_n; k++)
		{
			ShortestPath_DIJ(G, k);

			for (int i = 0; i < local_n; i++)
			{
				PathC(G, k, i);
			}

			for (int i = 0; i < local_n; i++)
			{
				if (ReturnD(i) == big)
				{//如果图不是全连通的
					T = 1;
				}
				Distance_total += ReturnD(i);
			}
		}
		if (T == 1)
			cout << "平均路径长度（此时重新计算了网络中各节点使用次数）：" << "∞" << endl;
		else
		{
			cout << "平均路径长度（此时重新计算了网络中各节点使用次数）：";
			cout << Distance_total / (local_n*(local_n - 1)) << endl;
		}
	}
	float HostToHostAverangeDistance(MatrixGraph<VerT, ArcT> &G, int display = 1,int count=1)
	{
		int T = 0;

		
			Distance_total = 0;
			if (count)
			{
				for (int i = 0; i < MAX_VERTEX_NUM; i++)
					C[i] = 0;
			}
			for (int k = 0; k < M; k++)
			{
				ShortestPath_DIJ(G, G.host[k].name);

				for (int i = 0; i < M; i++)
				{
					if (ReturnD(G.host[i].name) == big)
					{//如果图不是全连通的
						T = 1;
					}
					Distance_total += ReturnD(G.host[i].name);
				}

				//计算顶点使用次数
				if (count)
				{
					for (int m = 0; m < M; m++)
					{
						for (int n = 0; n < G.GetVexNumOrArcNum(0); n++)
						{
							if ((G.host[m].name != n) && (G.host[k].name != G.host[m].name))
								C[n] += G.ReturnGen(G.host[k].name)*P[G.host[m].name][n];
						}
					}
				}
			}
		
		totalC = 0;
		Cmax = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			totalC += C[i];
			if (Cmax < C[i])
			{
				Cmax = C[i];
				CmaxNode = i;
			}
		}
		Umax = (float)Cmax / totalC;
		
		if (display == 1)
		{
			if (T == 1)
				cout << "主机到主机平均路径长度（此时重新计算了网络中各节点使用次数）：" << "∞" << endl;
			else
			{
				cout << "主机到主机平均路径长度（此时重新计算了网络中各节点使用次数）：";
				cout << Distance_total / (M*(M - 1)) << endl;
			}
		}
		return Distance_total / (M*(M - 1));
	}
	float HostToHostEfficiency(MatrixGraph<VerT, ArcT> &G)
	{
			float Efficiency = 0;
			for (int k = 0; k < M; k++)
			{
				ShortestPath_DIJ(G, G.host[k].name);

				for (int i = 0; i < M; i++)
				{
					if (ReturnD(G.host[i].name) !=0)
					{
						Efficiency += (float)1 / ReturnD(G.host[i].name);
					}
				}
			}
			if (Efficiency / (M*(M - 1)) < 0.0001)
				Efficiency = 0;
			return Efficiency / (M*(M - 1));
	}
	void CoutHostToHostC(MatrixGraph<VerT, ArcT> &G)
	{//基于主机节点到各主机节点计算各点的使用次数，并找出最大的使用次数进行返回
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			C[i] = 0;
		}

		for (int i = 0; i < M; i++)
		{
			for (int m = 0; m < M; m++)
			{
				for (int n = 0; n < G.GetVexNumOrArcNum(0); n++)
				{
					if ((G.host[m].name != n) && (G.host[i].name != G.host[m].name))
						C[n] += G.ReturnGen(G.host[i].name)*ALLP[G.host[i].name][G.host[m].name][n];
				}
			}
		}

		totalC = 0;
		Cmax = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			totalC += C[i];
			if (Cmax < C[i])
			{
				Cmax = C[i];
				CmaxNode = i;
			}
		}
		Umax = (float)Cmax / totalC;
		cout <<"zaizheli"<< Cmax << "  "<<totalC<<"  " << Umax << "  ";
	}
	int ReturnCmaxNode()
	{
		return CmaxNode;
	}
	int ReturnCmax()
	{
		return Cmax;
	}
	float ReturnUmax()
	{
		return Umax;
	}
	int NearHostCmax(MatrixGraph<VerT, ArcT> &G)
	{
		int **DD;//分配M个最短距离表
		int ***PP;
		DD = new int*[M];
		for (int i = 0; i < M; i++)
			DD[i] = new int[G.GetVexNumOrArcNum(0)]();//后面的()能将开辟的动态数组初始化为0。

		PP = new int**[M];
		for (int i = 0; i < M; i++)
		{
			PP[i] = new int*[G.GetVexNumOrArcNum(0)];
			for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
			{
				PP[i][j] = new int[G.GetVexNumOrArcNum(0)]();
			}
		}

		for (int i = 0; i < M; i++)
		{
			ShortestPath_DIJ(G, G.host[i].name);
			for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
			{
				DD[i][j] = D[j];
				for (int k = 0; k < G.GetVexNumOrArcNum(0); k++)
				{
					PP[i][j][k] = P[j][k];
				}
			}
		}
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			C[i] = 0;
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
			for (int m = 0; m < G.GetVexNumOrArcNum(0); m++)
			{
				if (m != i&&m != G.host[NUMDD].name)
				{
					//cout << "din" << m << "  " << PP[NUMDD][i][m]<<endl;
					C[m] = C[m] + PP[NUMDD][i][m];//第i顶点到最近的j点通过的点
				}
			}
		}
		int v;//最大使用率的第v个顶点
		int total = 0;
		int max = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			total += C[i];
			if (max < C[i])
			{
				max = C[i];
				v = i;
			}
		}
		cout << "图中最大节点使用概率和次数：" << (float)max / total << "  " << max << endl;
		cout << "最大使用率节点和其度数:" << v << "  " << G.ReturnDeg(v) << endl;//当最大使用次数为0是会出错，此时主机能够直接一步发给需要服务的节点

		//删除相关的动态数组
		for (int i = 0; i < M; i++)
		{
			delete[]DD[i];
		}
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
			{
				delete[]PP[i][j];
			}
		}
		return max;
	}
	void MaxURN(MatrixGraph<VerT, ArcT> &G)
	{
		int v;//最大使用率的第v个顶点
		int total = 0;
		int max = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			total += C[i];
			if (max < C[i])
			{
				max = C[i];
				v = i;
			}
		}
		cout << "图中最大节点使用概率和次数：" << (float)max / total << "  " << max << endl;
		cout << "最大使用率节点和其度数:" << v << "  " << G.ReturnDeg(v) << endl;
	}
	void ShowhostC(MatrixGraph<VerT, ArcT> &G)
	{
		cout << "各host的使用次数为：";
		for (int i = 0; i < M; i++)
		{
			cout << C[G.host[i].name] << "  ";
		}
		cout << endl;
	}
	int ReturnC(int i)
	{
		return C[i];
	}
	int ReturnTotalC()
	{
		return totalC;
	}
	int ReturnAllTotalC()
	{
		return AllTotalC;;
	}
	void ShowPC(int i, int j)
	{
		cout << PC[i][j] << endl;
	}
};

#endif