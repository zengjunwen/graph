/*�β�wΪ�洢ͼ���ļ��������������飬ע���ͼ��Ҫ���Ƿ��нڵ�ı�ţ����ú����Ὣ�˻�����е�Cbestд�뵽asCbest.txt�У���������Ķ�д��degreeofhost.txt�У���Ѹ��ط���д��SAU(i).txt��*/
#include"random"
#include"ctime"
void SA(MatrixGraph<V, A> &g, int hostnum)
{
	g.HostNum = hostnum;
	ShortestPath<V, A> m;

	m.AverangeDistance(g);
	g.RandomHost();
	g.ShowHost();
	
	int Cbest, Cmax;
	int i = 1, j = 0, k, l, q;
	float T = 1000;
	m.CoutHostToHostC(g);
	Cmax = m.ReturnCmax();
	//Cmax = MAXGeneratedPackets(100, m.HostToHostAverangeDistance(g), M, m.HostToHostCmax(g, NULL, 1, 1, 1));
	Cbest = Cmax;

	uniform_int_distribution<unsigned> uu(0, M-1);
	uniform_int_distribution<unsigned> ww(0, g.GetVexNumOrArcNum(0)-1);
	uniform_int_distribution<unsigned> nn(0, 10000);
	default_random_engine e(time(0));

	char saCbest[20] = "saCbest.txt";
	ofstream fout(saCbest, ios::out);//���ͼ���ļ���ɾ��ԭ���ļ�������
	m.Countallshortpath(g);
	int step = 0;
	while (i)
	{

		//���ѡһ���ڵ���Ϊ�����ڵ�
		k = uu(e);
		l = ww(e);
		for (int a=0; a < M; a++)
		{
			if (g.host[a].name == l)
			{
				l =ww(e);
				a = 0;
			}
		}
		q = g.host[k].name;//��¼��������λ��ǰ������λ��
		g.host[k].name = l;
		m.CoutHostToHostC(g);
		Cmax = m.ReturnCmax();
		//Cmax = m.HostToHostCmax(g, NULL, 0, 1, 1);
		cout << endl;
		if (Cbest > Cmax)
		{
			Cbest = Cmax;
			j = 0;
		}
		else
		{
			if (nn(e) < (int)((exp((Cbest - Cmax)/T)) * 10000))
			{
			Cbest = Cmax;
			j ++;
			}
			else
			{
				g.host[k].name = q;
				m.CoutHostToHostC(g);
				Cmax = m.ReturnCmax();
				j++;
			}
		}
		fout << Cbest << endl;
		if (j == 15000)
			i = 0;
		step++;
		cout << "step" << step << endl;
		T=T*0.999;
	}
	fout.close();
		//g.host[0].name = 3;
		//g.host[1].name = 13;
		//g.host[2].name = 13;
	g.ShowHost();
	m.CoutHostToHostC(g);
	Cmax = m.ReturnCmax();
	m.ShowhostC(g);
	char d[20] = "degreeofhost.txt";
	ofstream fout1(d, ios::out);
	for (int i = 0; i < M; i++)
	{
		fout1 << g.ReturnDeg(g.host[i].name) << " ";
	}
	fout1.close();
	char w2[20] = "SAU(i).txt";
	m.CoutHostToHostC(g);
	MAXGeneratedPackets(100, m.HostToHostAverangeDistance(g), M, m.ReturnCmax());
	//g.DFSTraverse(Visit);
	//m.ShowPC(0,1);
	//m.ShowPC(1,0);
}