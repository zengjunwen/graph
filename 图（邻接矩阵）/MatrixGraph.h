//MatrixGraph.h图的邻接矩阵类
//数组：顶点、弧、顶点度、主机
#ifndef _MATRIXGRAPH_H_
#define _MSTRIXGRAPH_H_
#include "agraph.h"
template<typename VerT, typename ArcT>class MatrixGraph :public AGraph<VerT>
{//定义弧结构ArcT模板并继承AGraph<VerT>的邻接矩阵类
protected:
	int VexNum;//图的顶点数
	VerT *vexs=new VerT[MAX_VERTEX_NUM];//顶点向量组
	
	ArcT **arcs;//邻接矩阵，存储弧的信息
	int *Deg=new int[MAX_VERTEX_NUM];//存储顶点的度
public:
	int HostNum;//主机个数
	VerT *host=new VerT[M];//主机节点数组
	MatrixGraph()
	{//构造一个空图
		arcs = new ArcT*[MAX_VERTEX_NUM];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			vexs[i].Gen = 1;//默认每个节点产生生数据的速率为1
			arcs[i] = new ArcT[MAX_VERTEX_NUM];
		}
	VexNum = ArcNum =HostNum= 0;

	}
	~MatrixGraph()
	{
		delete[]vexs;
		delete[]Deg;
		delete[]host;
		for (int i=0; i < MAX_VERTEX_NUM; i++)
		{
			delete[]arcs[i];
		}
		cout <<"删除与图中基本的动态数组" << endl;
	}
	void CopyTo(MatrixGraph<VerT, ArcT> &G)
	{
		G.VexNum = VexNum;
		G.ArcNum = ArcNum;
		for (int i=0; i < MAX_VERTEX_NUM; i++)
		{
			for (int j=0; j < MAX_VERTEX_NUM; j++)
			{
				G.arcs[i][j] = arcs[i][j];
			}
			G.vexs[i] = vexs[i];
			G.Deg[i] = Deg[i];
		}
		G.HostNum =HostNum;
		for (int i=0; i < HostNum; i++)
		{
			G.host[i] = host[i];
		}
	}
	int LocateVex(VerT u)const
	{//返回与u有相同特征（关键字）的顶点的序号
		int i;
		for (i = 0; i < VexNum; ++i)
			if (u.name == vexs[i].name)
				return i;
		return -1;
	}
	void DestroyGraph()
	{//销毁图
		for (int i = VexNum - 1; i >= 0; i--)
			DeleteVex(vexs[i].name);//从大到小删除顶点与其相关的弧
	}
	void CreateFromFile(string FileName)
	{
		int i, j, k;
		VRType w =big;
		VerT v1, v2;
		ifstream fin(FileName);
		fin >> boolalpha >> Directed;
		fin >> boolalpha >> Weight;
		if (Weight)
			w = big;
		fin >> VexNum;
		for (i = 0; i < VexNum; ++i)
			//InputVertexFromFile(fin, vexs[i]);
			vexs[i].name = i;
		fin >> ArcNum;
		for (i = 0; i<VexNum; ++i)
			for (j = 0; j<VexNum; ++j)
				arcs[i][j].adj = w;
		if (Weight)
			for (i = 0; i<VexNum; ++i)
				arcs[i][i].adj = 0;
		if (!Weight)
			w = 1;
		for (k = 0; k<ArcNum; ++k)
		{
			InputVertexNameFromFile(fin, v1);
			InputVertexNameFromFile(fin, v2);
			if (Weight)
				fin >> w;
			i = LocateVex(v1);
			j = LocateVex(v2);
			arcs[i][j].adj = w;
			InputArcFromFile(fin, arcs[i][j]);
			if (!Directed)
				arcs[j][i] = arcs[i][j];
		}
		for (int i = 0; i < VexNum; i++)
		{
			arcs[i][i].adj = 0;
		}
		fin.close();
	}
	void CreateFromFileN(char* FileName)
	{
		int i, j, k;
		VRType w = big;
		VerT v1, v2;
		ifstream fin(FileName);
		fin >> boolalpha >> Directed;
		fin >> boolalpha >> Weight;
		if (Weight)
			w = big;
		fin >> VexNum;
		for (i = 0; i < VexNum; ++i)
			InputVertexFromFile(fin, vexs[i]);
		fin >> ArcNum;
		for (i = 0; i<VexNum; ++i)
			for (j = 0; j<VexNum; ++j)
				arcs[i][j].adj = w;
		if (Weight)
			for (i = 0; i<VexNum; ++i)
				arcs[i][i].adj = 0;
		if (!Weight)
			w = 1;
		for (k = 0; k<ArcNum; ++k)
		{
			InputVertexNameFromFile(fin, v1);
			InputVertexNameFromFile(fin, v2);
			if (Weight)
				fin >> w;
			i = LocateVex(v1);
			j = LocateVex(v2);
			arcs[i][j].adj = w;
			InputArcFromFile(fin, arcs[i][j]);
			if (!Directed)
				arcs[j][i] = arcs[i][j];
		}
		for (int i = 0; i < VexNum; i++)
		{
			arcs[i][i].adj = 0;
		}
		fin.close();
	}
	void CreateToFile(char* FileName)
	{
		int i, j, k;
		ofstream fout(FileName, ios::out);//输出图到文件并删除原来文件的内容
		fout << boolalpha << Directed << endl;
		fout << boolalpha << Weight << endl;
		fout << VexNum << endl;//输出vector vexs的个数，即顶点个数
		j = VexNum;
		/*for (i = 0; i < j; i++)
		{
			fout << i << ' ';
		}*/
		//fout << endl;
		fout << ArcNum << endl;
		for (k = 0; k < j; k++)
		{
			if (Directed==1)
			{
				for (int r = 0; r < j; r++)
				{
					if (arcs[k][r].adj < big&&k != r)
					{
						fout << k << ' ';
						fout << r << ' ';
						if (Weight)
							fout << arcs[k][r].adj;
						fout << endl;
					}
				}
			}
			else
			{
				for (int r = k+1; r < j; r++)
				{
					if (arcs[k][r].adj < big&&k != r)
					{
						fout << k << ' ';
						fout << r << ' ';
						if (Weight)
							fout << arcs[k][r].adj;
						fout << endl;
					}
				}
			}
		}
		fout.close();
	}
	void Sethost(char* FileName)
	{
		ifstream fin(FileName);
		fin>>HostNum;
		for (int i=0; i < HostNum;i++)
			fin >> host[i].name;
		fin.close();
	}
	void OutputHost(char* FileName)
	{
		ofstream fout(FileName, ios::out);
		fout <<HostNum<<endl;
		for (int i = 0; i < HostNum; i++)
		{
			fout << host[i].name<<" ";
		}
		fout.close();
	}
	bool PutVex(VerT v, VerT value)
	{//对顶点v赋新值value
		int k = LocateVex(v);//k为顶点v在图中的序号
		if (k < 0)//不存在顶点v
			return false；
			vexs[k] = value;//将新值赋给顶点v
		return ture;
	}
	void ChangeGen(int i, int j)
	{
		vexs[i].Gen = j;
	}
	float ReturnGen(int i) const
	{
		return vexs[i].Gen;
	}
	void Changename(int i, int j)
	{
		vexs[i].name = j;
	}
	void ChangeCap(int i, float j)
	{
		vexs[i].Cap = j;
	}
	float returnCap(int i)
	{
		return vexs[i].Cap;
	}
	void InsertVex(VerT v)
	{//在图中增加新顶点v（弧由InsertArc（）去做）
		int i;
		int j = big;
		if (Weight)//带权图
			j =big;
		vexs[VexNum] = v;
		for (i = 0; i < VexNum; i++)
			arcs[VexNum][i].adj = arcs[i][VexNum].adj = j;
		arcs[VexNum][VexNum].adj = 0;
		VexNum++;
	}
	void InsertVex(int v)
	{//在图中增加新顶点v（弧由InsertArc（）去做）
		int i;
		int j = big;
		if (Weight)//带权图
			j = big;
		vexs[VexNum].name = v;
		for (i = 0; i < VexNum; i++)
			arcs[VexNum][i].adj = arcs[i][VexNum].adj = j;
		arcs[VexNum][VexNum].adj = 0;
		VexNum++;
	}
	bool DeleteVex(int v)
	{//删除图中的顶点v及其相关的边
		int i, j, k;
		k = v;
		if (k < 0)
			return false;
		for (i = 0; i < VexNum; i++)
			DeleteArc(vexs[k], vexs[i]);
		if (Directed)
		for (i = 0; i < VexNum; i++)
			DeleteArc(vexs[i], vexs[k]);
		for (j = k + 1; j < VexNum; j++)
			vexs[j - 1] = vexs[j];//[k]后面的顶点依次前移
		for (i=0;i<VexNum;i++)
		for (j = k + 1; j < VexNum; j++)
			arcs[i][j - 1] = arcs[i][j];
		for (i = 0; i<VexNum; i++)
		for (j = k + 1; j < VexNum; j++)
			arcs[j-1][i] = arcs[j][i];
		VexNum--;
		return true;
	}
	bool DeleteArcsOfVex(int v)
	{//删除图中的顶点v及其相关的边
		int i, j, k;
		k = v;
		if (k < 0)
			return false;
		for (i = 0; i < VexNum; i++)
			DeleteArc(vexs[k], vexs[i]);
		if (Directed)
			for (i = 0; i < VexNum; i++)
				DeleteArc(vexs[i].name, vexs[k].name);
		return true;
	}
	bool InsertArc(VerT v, VerT w)
	{//v和w是图中的两个顶点，增添弧<v,w>，若是无向的，则还要添加<w,v>
		int i, j;
		i = LocateVex(v);
		j = LocateVex(w);
		if (i < 0 || j < 0)//不存在顶点v或w
			return false;
		ArcNum++;
		if (Weight)
		{
			cout << "请输入此弧的带权值：";
				cin >> arcs[i][j].adj;
		}
		else
			arcs[i][j].adj = 1;
		if (!Directed)
		arcs[j][i] = arcs[i][j];
		return true;
	}
	bool InsertArc(int v, int w)
	{//v和w是图中的两个顶点，增添弧<v,w>，若是无向的，则还要添加<w,v>
		if (arcs[v][w].adj == 1||v==w)
			return false;
		ArcNum++;
		if (Weight)
		{
			cout << "请输入此弧的带权值：";
			cin >> arcs[v][w].adj;
		}
		else
			arcs[v][w].adj = 1;
		if (!Directed)
			arcs[w][v] = arcs[v][w];
		return true;
	}
	bool DeleteArc(VerT v, VerT w)
	{//v和w是图中的两个顶点。删除弧<v,w>,若是无向的，则还删除弧<w,v>
		int i, k;
		int j = big;
		if (Weight)
			j = big;
		i = LocateVex(v);
		k = LocateVex(w);
		if (i < 0 || k < 0 || i == k)
			return false;
		if (arcs[i][k].adj != j)
		{
			arcs[i][k].adj = j;
			if (!Directed)
				arcs[k][i].adj = arcs[i][k].adj;
			ArcNum--;
		}
		return true;
	}
	bool DeleteArc(int v, int w)
	{//v和w是图中的两个顶点。删除弧<v,w>,若是无向的，则还删除弧<w,v>
		int i, k;
		int j = 0;
		if (Weight)
			j = big;
		i = v;
		k = w;
		if (i < 0 || k < 0 || i == k)
			return false;
		if (arcs[i][k].adj != j)
		{
			arcs[i][k].adj = j;
			if (!Directed)
				arcs[k][i] = arcs[i][k];
			ArcNum--;
		}
		return true;
	}
	int Getarcs(int i, int j)
	{
		return arcs[i][j].adj;
	}
	int FirstAdjVex(int i)const
	{//返回顶点[i]的第一个邻接顶点的序号。
			int j = big;
		for (int k = 0; k<VexNum; k++)
			if (i != k && arcs[i][k].adj != j)
				return k;
		return -1;
	}
	int NextAdjVex(int i, int j)const
	{//返回顶点[i]（相对于顶点[j]）的下一个邻接顶点的序号。
		int m = big;
		for (int k = j + 1; k<VexNum; k++)
			if (i != k && arcs[i][k].adj != m)
				return k;
		return -1;
	}
	VerT GetVex(int i)const
	{//返回顶点[i]的值
		if (i >= VexNum || i < 0)
			exit(1);
		return vexs[i];//返回该顶点的信息

	}
	ArcT GetArc(int i, int j)const
	{//返回弧<i,j>的信息
		return arcs[i][j];
	}
	void Display()const
	{//输出邻接矩阵存储结构的图
		int i, j;
		string s1 = "无向",s2 = "无权图";
		if (Directed)
			s1 = "有向";
		if (Weight)
			s2 = "带权图";
		cout << VexNum << "个顶点" << ArcNum << "条弧的" << s1 << s2 << "。顶点依次是：";
		for (i = 0; i < VexNum; i++)
			cout << vexs[i].name << " ";
		cout << endl << "arcs.adj:" << endl;
		for (i = 0; i < VexNum; i++)
		{
			for (j = 0; j < VexNum;j++)
			if (arcs[i][j].adj ==big)
				cout << "∞" << ' ';
			else
				cout << arcs[i][j].adj << "  ";
			cout << endl;
		}

	}
	int GetVexNumOrArcNum(int i)const
	{//返回图的顶点数（i=0）或弧数（i=1）
		if (i == 0)
			return VexNum;
		else
			return ArcNum;

	}

	void RandomHost()
	{
		//主机位置随机确定,需要知道顶点个数
		uniform_int_distribution<unsigned> uu(0, VexNum-1);
		default_random_engine e(time(0));
		for (int i = 0; i < M; i++)
		{
			int k=uu(e);
			for (int j = 0; j < i; j++)
			{
				if (k == host[j].name)
				{
					k=uu(e);
					j=0;
				}
			}
			host[i].name = k;
		}
	}
	void ShowHost()
	{
		cout << "主机节点为：";
			for (int i = 0; i < HostNum; i++)
			{
				cout << host[i].name << " ";
			}
		cout << endl;
	}

	void Random()
	{
		int i, j;
		float f;
		V v;
		v.name = 0;
		srand((int)time(0));//产生一个以当前时间开始的随机数种子
		cout << "输入顶点数：";
		cin >> i;
		cout << endl;
		j = i;
		cout << "输入边数：";
		cin >> f;
		for (i; i > 0; i--)
		{
			InsertVex(v);
			v.name++;
		}
		uniform_int_distribution<unsigned> uu(0, j-1);
		default_random_engine e(time(0));
		for (f; f > 0; f--)
		{
			while (InsertArc(vexs[uu(e)], vexs[uu(e)])!=true)
				{
					
				}
		}

	}
	void CountDegree(int choice=0)
	{
		for (int i = 0; i < VexNum; i++)
		{//计算每个顶点的度
			Deg[i] = 0;
			for (int j = 0; j < VexNum; j++)
			{
				if (arcs[i][j].adj < big&&arcs[i][j].adj)
					Deg[i] += 1;
			}
			//cout << Deg[i] << " ";
		}
		if (choice == 1)
		{
			char w[20] = "degree.txt";
			ofstream fout(w, ios::out);
			for (int i = 0; i < VexNum; i++)
			{
				fout << Deg[i] << endl;
			}
			fout.close();
		}
		//cout << endl;
	}
	void BA()
	{//会把每个节点生成数据的数率设为0
		srand((int)time(0));
		char r[11] = "INITBA.txt";
		CreateFromFileN(r);
		int total = 2 * ArcNum;
		int Vnum,Anum;
		cout << "输入BA网络的顶点数（至少为3个,查看初始网络是否正确！）" << endl;
		//cin >> Vnum;
		Vnum = 500;
		Vnum = Vnum - 4;
		cout << "输入每个新插入顶点的连边数" << endl;
		//cin >> Anum;
		Anum = 4;
		V v;
		v.name = VexNum - 1;
		CountDegree();
		for (int i = 0; i < Vnum; i++)
		{//插入新加入的顶点
			v.name++;
			InsertVex(v);
			Deg[VexNum - 1] = 0;
			for (int m = 0; m < Anum; m++)
			{
				int b = rand() % total;
				int c = 0;
				for (int j = 0; j < VexNum+1; j++)
				{
					if (c > b)
					{
						InsertArc((VexNum - 1),(j - 1));
						Deg[VexNum - 1] += 1;
						total -= Deg[j-1];
						Deg[j - 1] += 1;
						j = VexNum+1;
					}
					else
					{
						if (arcs[VexNum-1][j].adj!=1)
						c += Deg[j];
					}
				}
			}
			total = 2 * ArcNum;
		}
		CountDegree();
	}
	void K_CORE(int k)
	{
		CountDegree();
		int u = GetVexNumOrArcNum(0);
		for (int j = u; j>0; j--)
		{
			if (ReturnDeg(j-1) == k || ReturnDeg(j-1)<k)
			{
				DeleteVex(vexs[j-1]);
				j = GetVexNumOrArcNum(0)+1;//+1很重要，因为在下一次for循环要先减1
				CountDegree();
				//cout << "节点：";
				//g.DFSTraverse(Visit);
			}
		}
	}
	int ReturnDeg(int v)
	{//返回第v个顶点的度
		return Deg[v];
	}
	int ReturnVexs(int i)
	{
		return vexs[i].name;
	}
	void CopyVexs(VerT *p)
	{
		for (int i = 0; i < GetVexNumOrArcNum(0); i++)
		{
				p[i]= vexs[i];	
		}
	}

	friend void OneByOneChoiceHost(MatrixGraph<typename VerT, typename ArcT>&g, int hostnum);
};

#endif