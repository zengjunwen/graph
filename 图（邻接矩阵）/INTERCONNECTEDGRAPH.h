#ifndef _INTERCONNECTEDGRAPH_H_
#define _INTERCONNECTEDGRAPH_H_
#include"random"
int INGMyCompare(const void * elem1, const void * elem2)
{
	int * p1, *p2;
	p1 = (int *)elem1; // �� * elem1�� �Ƿ�
	p2 = (int *)elem2; // �� * elem2�� �Ƿ�
	return (*p2 - *p1);
}
template<typename VerT,typename ArcT>
class InterconnectedGraph
{
private:
	MatrixGraph<VerT, ArcT> G1;
	MatrixGraph<VerT, ArcT> G2;
	MatrixGraph<VerT, ArcT> G3;
	
public:
	InterconnectedGraph(MatrixGraph<VerT, ArcT> &g1, MatrixGraph<VerT, ArcT> &g2)
	{
		g1.CopyTo(G1);
		g2.CopyTo(G2);
	}
	~InterconnectedGraph()
	{
		
	}
	void ConnectedMethod(float p,int choice);
};
template<typename VerT,typename ArcT>
void InterconnectedGraph<VerT, ArcT>::ConnectedMethod(float p,int choice)
{//pΪ���Ӹ���
	G1.CopyTo(G3);

	int *an1 = new int[G1.GetVexNumOrArcNum(0)];//���ڴ�����ɴ�С��˳��
	int *an2 = new int[G2.GetVexNumOrArcNum(0)];
	int *an3 = new int[G1.HostNum];
	int *an4 = new int[G2.HostNum];
	int *Vext1 = new int[G1.GetVexNumOrArcNum(0)];//���ڴ洢�ڵ��ɴ�С�Ľڵ��˳��
	int *Vext2 = new int[G2.GetVexNumOrArcNum(0)];
	int *HostVext1 = new int[G1.HostNum];
	int *HostVext2 = new int[G2.HostNum];

	//����Ȳ���an�и�ֵ
	G1.CountDegree();
	G2.CountDegree();
	for (int i = 0; i < G1.GetVexNumOrArcNum(0); i++)
	{
		an1[i] = G1.ReturnDeg(i);
		if (i<G1.HostNum)
		{
			an3[i] = G1.ReturnDeg(G1.host[i].name);
		}
		//cout << an1[i]<<endl;
	}
	for (int i = 0; i < G2.GetVexNumOrArcNum(0); i++)
	{
		an2[i] = G2.ReturnDeg(i);
		if (i<G2.HostNum)
		{
			an4[i] = G2.ReturnDeg(G2.host[i].name);
		}
		//cout << an2[i]<<endl;
	}

	//������
	qsort(an1, G1.GetVexNumOrArcNum(0), sizeof(int), INGMyCompare);
	qsort(an2, G2.GetVexNumOrArcNum(0), sizeof(int), INGMyCompare);
	qsort(an3, G1.HostNum, sizeof(int), INGMyCompare);
	qsort(an4, G2.HostNum, sizeof(int), INGMyCompare);

	//��G1��G2�еĶ��㰴�ȴ�С�����������Vext1��Vext2����������
	for (int j = 0; j < G1.GetVexNumOrArcNum(0); j++)
	{
		for (int n = 0; n < G1.GetVexNumOrArcNum(0); n++)
		{
			if (G1.ReturnDeg(n) == an1[j])
			{
				int ture = 1;
				for (int k = 0; k < j; k++)
				{
					if (Vext1[k] == n)
						ture = 0;
				}
				if (ture == 1)
				{
					Vext1[j] = n;
					//cout << n << "  " << G1.ReturnDeg(n)<< endl;
				}
			}
		}
	}
	for (int j = 0; j < G2.GetVexNumOrArcNum(0); j++)
	{
		for (int n = 0; n < G2.GetVexNumOrArcNum(0); n++)
		{
			if (G2.ReturnDeg(n) == an2[j])
			{
				int ture = 1;
				for (int k = 0; k < j; k++)
				{
					if (Vext2[k] == n)
						ture = 0;
				}
				if (ture == 1)
				{
					Vext2[j] = n;
					//cout << G2.ReturnVexs(n) << "  " << G2.ReturnDeg(n) << endl;
				}
			}
		}
	}
	for (int j = 0; j < G1.HostNum; j++)
	{
		for (int n = 0; n < G1.HostNum; n++)
		{
			if (G1.ReturnDeg(G1.host[n].name) == an3[j])
			{
				int ture = 1;
				for (int k = 0; k < j; k++)
				{
					if (HostVext1[k] == G1.host[n].name)
						ture = 0;
				}
				if (ture == 1)
				{
					HostVext1[j] = G1.host[n].name;
					//cout << G2.ReturnVexs(n) << "  " << G2.ReturnDeg(n) << endl;
				}
			}
		}
	}
	for (int j = 0; j < G2.HostNum; j++)
	{
		for (int n = 0; n < G2.HostNum; n++)
		{
			if (G2.ReturnDeg(G2.host[n].name) == an4[j])
			{
				int ture = 1;
				for (int k = 0; k < j; k++)
				{
					if (HostVext2[k] == G2.host[n].name)
						ture = 0;
				}
				if (ture == 1)
				{
					HostVext2[j] = G2.host[n].name;
					//cout << G2.ReturnVexs(n) << "  " << G2.ReturnDeg(n) << endl;
				}
			}
		}
	}
	//��ͼG2���нڵ�����֣��������������֣�Ŀ��Ϊ�˽ڵ��˳��Ϊ����˳��
	for (int i = 0; i < G2.GetVexNumOrArcNum(0); i++)
	{
		G2.ChangeVex(i, i + G1.GetVexNumOrArcNum(0));
		Vext2[i] = Vext2[i] + G1.GetVexNumOrArcNum(0);
	}
	for (int i = 0; i < M; i++)
	{
		G2.host[i].name = G2.host[i].name + G1.GetVexNumOrArcNum(0);
	}
	for (int i = 0; i < G2.HostNum; i++)
	{
		HostVext2[i] += G1.GetVexNumOrArcNum(0);
	}
	//��G2���뵽G3��
	for (int i = 0; i < G2.GetVexNumOrArcNum(0); i++)
	{
		G3.InsertVex(G2.ReturnVexs(i));
	}
	for (int i = 0; i < G2.GetVexNumOrArcNum(0); i++)
	{
		for (int j = i + 1; j < G2.GetVexNumOrArcNum(0);j++)
		if (G2.GetArc(i, j).adj == 1)
		{
			G3.InsertArc(i + G1.GetVexNumOrArcNum(0), j + G1.GetVexNumOrArcNum(0));
		}
	}

	//��G2���������뵽G3��
	G3.HostNum +=G2.HostNum;
	cout << G3.HostNum;
	for (int i = 0; i < G2.HostNum; i++)
	{
		G3.host[G1.HostNum + i] = G2.host[i];
	}
	//G1.Display();
	//G2.Display();
	//G3.Display();

	//������p����ͼ���ȴ�С��˳����������
	int N, M;//NΪ��ͼ����С�Ķ�����
		N = G1.GetVexNumOrArcNum(0);
		M = G2.GetVexNumOrArcNum(0);
	uniform_int_distribution<unsigned> nn(1, 10000);
	uniform_int_distribution<unsigned> mm(0, M - 1);//����ͼ���������
	uniform_int_distribution<unsigned> hh(0, G1.HostNum-1);
	default_random_engine e(time(0));
	int *a = new int[N];//�������G1��G1���Ѿ�����һ��ͼ���ӵļ���
	switch (choice)
	{
	case 1:
		for (int i = 0; i < N; i++)
		{
			//cout << Vext1[i] << " " << Vext2[i] << "dfd";
			if (nn(e) < (int)(p * 10000))
				G3.InsertArc(Vext1[i], Vext2[i]);
		}
		break;
	case 2:
		for (int i = 0; i < N; i++)
		{
			if (nn(e) < (int)(p * 10000))
				G3.InsertArc(Vext1[i], Vext2[G2.GetVexNumOrArcNum(0) - 1 - i]);
		}
		break;
	case 3:
		int v2;
		for (int i = 0; i < N; i++)
		{
			v2 = mm(e);
			for (int j = 0; j < i; j++)
			{
				if (v2 == a[j])
				{
					v2 = mm(e);
					j = 0;
				}
			}
			if (nn(e) < (int)(p * 10000))
			{
				a[i] = v2;
				G3.InsertArc(Vext1[i], Vext2[v2]);
			}
		}
		break;
	case 4:
		for (int i = 0; i < (int)(p*N); i++)
		{
			//cout << Vext1[i] << " " << Vext2[i] << "dfd";
			G3.InsertArc(Vext1[i], Vext2[i]);
		}
		break;
	case 5:
		for (int i = 0; i < (int)(p*N); i++)
		{
			//cout << Vext1[i] << " " << Vext2[i] << "dfd";
			G3.InsertArc(Vext1[i], Vext2[G2.GetVexNumOrArcNum(0) - 1 - i]);
		}
		break;
	case 6:
		for (int i = 0; i < (int)(p*N); i++)
		{
			//cout << Vext1[i] << " " << Vext2[i] << "dfd";
			G3.InsertArc(HostVext1[i], HostVext2[i]);
		}
		break;
	case 7:
		for (int i = 0; i < (int)(p*N); i++)
		{
			//cout << Vext1[i] << " " << Vext2[i] << "dfd";
			G3.InsertArc(HostVext1[i], HostVext2[G2.HostNum - 1 - i]);
		}
		break;
	case 8:
		for (int i = 0; i < N; i++)
		{
			v2 = hh(e);
			for (int j = 0; j < i; j++)
			{
				if (v2 == a[j])
				{
					v2 = hh(e);
					j = 0;
				}
			}
			if (nn(e) < (int)(p * 10000))
			{
				a[i] = v2;
				G3.InsertArc(Vext1[i], Vext2[v2]);
			}
		}
		break;
	}
	delete[]a;
	//G3.Display();
	G3.CreateToFile(w);
	G3.ShowHost();
	//ɾ�����ٵĶ�̬����
	delete[]an1;
	delete[]an2;
	delete[]Vext1;
	delete[]Vext2;
}

#endif