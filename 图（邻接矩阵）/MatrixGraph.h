//MatrixGraph.hͼ���ڽӾ�����
//���飺���㡢��������ȡ�����
#ifndef _MATRIXGRAPH_H_
#define _MSTRIXGRAPH_H_
#include "agraph.h"
template<typename VerT, typename ArcT>class MatrixGraph :public AGraph<VerT>
{//���廡�ṹArcTģ�岢�̳�AGraph<VerT>���ڽӾ�����
protected:
	int VexNum;//ͼ�Ķ�����
	VerT *vexs=new VerT[MAX_VERTEX_NUM];//����������
	
	ArcT **arcs;//�ڽӾ��󣬴洢������Ϣ
	int *Deg=new int[MAX_VERTEX_NUM];//�洢����Ķ�
public:
	int HostNum;//��������
	VerT *host=new VerT[M];//�����ڵ�����
	MatrixGraph()
	{//����һ����ͼ
		arcs = new ArcT*[MAX_VERTEX_NUM];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			vexs[i].Gen = 1;//Ĭ��ÿ���ڵ���������ݵ�����Ϊ1
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
		cout <<"ɾ����ͼ�л����Ķ�̬����" << endl;
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
	{//������u����ͬ�������ؼ��֣��Ķ�������
		int i;
		for (i = 0; i < VexNum; ++i)
			if (u.name == vexs[i].name)
				return i;
		return -1;
	}
	void DestroyGraph()
	{//����ͼ
		for (int i = VexNum - 1; i >= 0; i--)
			DeleteVex(vexs[i].name);//�Ӵ�Сɾ������������صĻ�
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
		ofstream fout(FileName, ios::out);//���ͼ���ļ���ɾ��ԭ���ļ�������
		fout << boolalpha << Directed << endl;
		fout << boolalpha << Weight << endl;
		fout << VexNum << endl;//���vector vexs�ĸ��������������
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
	{//�Զ���v����ֵvalue
		int k = LocateVex(v);//kΪ����v��ͼ�е����
		if (k < 0)//�����ڶ���v
			return false��
			vexs[k] = value;//����ֵ��������v
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
	{//��ͼ�������¶���v������InsertArc����ȥ����
		int i;
		int j = big;
		if (Weight)//��Ȩͼ
			j =big;
		vexs[VexNum] = v;
		for (i = 0; i < VexNum; i++)
			arcs[VexNum][i].adj = arcs[i][VexNum].adj = j;
		arcs[VexNum][VexNum].adj = 0;
		VexNum++;
	}
	void InsertVex(int v)
	{//��ͼ�������¶���v������InsertArc����ȥ����
		int i;
		int j = big;
		if (Weight)//��Ȩͼ
			j = big;
		vexs[VexNum].name = v;
		for (i = 0; i < VexNum; i++)
			arcs[VexNum][i].adj = arcs[i][VexNum].adj = j;
		arcs[VexNum][VexNum].adj = 0;
		VexNum++;
	}
	bool DeleteVex(int v)
	{//ɾ��ͼ�еĶ���v������صı�
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
			vexs[j - 1] = vexs[j];//[k]����Ķ�������ǰ��
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
	{//ɾ��ͼ�еĶ���v������صı�
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
	{//v��w��ͼ�е��������㣬����<v,w>����������ģ���Ҫ���<w,v>
		int i, j;
		i = LocateVex(v);
		j = LocateVex(w);
		if (i < 0 || j < 0)//�����ڶ���v��w
			return false;
		ArcNum++;
		if (Weight)
		{
			cout << "������˻��Ĵ�Ȩֵ��";
				cin >> arcs[i][j].adj;
		}
		else
			arcs[i][j].adj = 1;
		if (!Directed)
		arcs[j][i] = arcs[i][j];
		return true;
	}
	bool InsertArc(int v, int w)
	{//v��w��ͼ�е��������㣬����<v,w>����������ģ���Ҫ���<w,v>
		if (arcs[v][w].adj == 1||v==w)
			return false;
		ArcNum++;
		if (Weight)
		{
			cout << "������˻��Ĵ�Ȩֵ��";
			cin >> arcs[v][w].adj;
		}
		else
			arcs[v][w].adj = 1;
		if (!Directed)
			arcs[w][v] = arcs[v][w];
		return true;
	}
	bool DeleteArc(VerT v, VerT w)
	{//v��w��ͼ�е��������㡣ɾ����<v,w>,��������ģ���ɾ����<w,v>
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
	{//v��w��ͼ�е��������㡣ɾ����<v,w>,��������ģ���ɾ����<w,v>
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
	{//���ض���[i]�ĵ�һ���ڽӶ������š�
			int j = big;
		for (int k = 0; k<VexNum; k++)
			if (i != k && arcs[i][k].adj != j)
				return k;
		return -1;
	}
	int NextAdjVex(int i, int j)const
	{//���ض���[i]������ڶ���[j]������һ���ڽӶ������š�
		int m = big;
		for (int k = j + 1; k<VexNum; k++)
			if (i != k && arcs[i][k].adj != m)
				return k;
		return -1;
	}
	VerT GetVex(int i)const
	{//���ض���[i]��ֵ
		if (i >= VexNum || i < 0)
			exit(1);
		return vexs[i];//���ظö������Ϣ

	}
	ArcT GetArc(int i, int j)const
	{//���ػ�<i,j>����Ϣ
		return arcs[i][j];
	}
	void Display()const
	{//����ڽӾ���洢�ṹ��ͼ
		int i, j;
		string s1 = "����",s2 = "��Ȩͼ";
		if (Directed)
			s1 = "����";
		if (Weight)
			s2 = "��Ȩͼ";
		cout << VexNum << "������" << ArcNum << "������" << s1 << s2 << "�����������ǣ�";
		for (i = 0; i < VexNum; i++)
			cout << vexs[i].name << " ";
		cout << endl << "arcs.adj:" << endl;
		for (i = 0; i < VexNum; i++)
		{
			for (j = 0; j < VexNum;j++)
			if (arcs[i][j].adj ==big)
				cout << "��" << ' ';
			else
				cout << arcs[i][j].adj << "  ";
			cout << endl;
		}

	}
	int GetVexNumOrArcNum(int i)const
	{//����ͼ�Ķ�������i=0��������i=1��
		if (i == 0)
			return VexNum;
		else
			return ArcNum;

	}

	void RandomHost()
	{
		//����λ�����ȷ��,��Ҫ֪���������
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
		cout << "�����ڵ�Ϊ��";
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
		srand((int)time(0));//����һ���Ե�ǰʱ�俪ʼ�����������
		cout << "���붥������";
		cin >> i;
		cout << endl;
		j = i;
		cout << "���������";
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
		{//����ÿ������Ķ�
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
	{//���ÿ���ڵ��������ݵ�������Ϊ0
		srand((int)time(0));
		char r[11] = "INITBA.txt";
		CreateFromFileN(r);
		int total = 2 * ArcNum;
		int Vnum,Anum;
		cout << "����BA����Ķ�����������Ϊ3��,�鿴��ʼ�����Ƿ���ȷ����" << endl;
		//cin >> Vnum;
		Vnum = 500;
		Vnum = Vnum - 4;
		cout << "����ÿ���²��붥���������" << endl;
		//cin >> Anum;
		Anum = 4;
		V v;
		v.name = VexNum - 1;
		CountDegree();
		for (int i = 0; i < Vnum; i++)
		{//�����¼���Ķ���
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
				j = GetVexNumOrArcNum(0)+1;//+1����Ҫ����Ϊ����һ��forѭ��Ҫ�ȼ�1
				CountDegree();
				//cout << "�ڵ㣺";
				//g.DFSTraverse(Visit);
			}
		}
	}
	int ReturnDeg(int v)
	{//���ص�v������Ķ�
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