#include"random"
#include"ctime"

int LDSACompare(const void * elem1, const void * elem2)
{
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p1 - *p2);
}
void LDSA(int MAX_VERTEX_NUM_a, int M_b)
{
	const float rate = 0.5;
	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;


	MatrixGraph<V, A> g;
	ShortestPath<V, A> m;

	g.CreateFromFile(r);
	g.CountDegree();
	m.AverangeDistance(g);
	int *an = new int[g.GetVexNumOrArcNum(0)];
	int *UDHost = new int[g.GetVexNumOrArcNum(0)];
	for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
	{
		an[i] = g.ReturnDeg(i);
		//cout << an[i]<<endl;
	}
	qsort(an, g.GetVexNumOrArcNum(0), sizeof(int), LDSACompare);
	for (int j = 0; j < (int)g.GetVexNumOrArcNum(0)*rate; j++)
	{
		for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
		{
			if (g.ReturnDeg(n) == an[j])
			{
				int ture = 1;
				for (int k = 0; k < j; k++)
				{
					if (UDHost[k] == n)
						ture = 0;
				}
				if (ture == 1)
				{
					UDHost[j] = n;
					//cout << n << endl;
				}
			}
		}
	}
	//m.MaxURN(g);
	g.RandomHost();
	g.ShowHost();
	//g.CreateToFile(w);

	int Cbest, Cmax;
	int i = 1, j = 0, k, l, q, T = 10000;
	Cmax = m.HostToHostCmax(g);
	Cbest = Cmax;

	uniform_int_distribution<unsigned> uu(0, M - 1);
	uniform_int_distribution<unsigned> ww(0, (int)g.GetVexNumOrArcNum(0)*rate);
	uniform_int_distribution<unsigned> nn(0, 10000);
	default_random_engine e(time(0));
	while (i)
	{

		//随机选一个节点做为主机节点
		k = uu(e);
		l = ww(e);
		for (int a = 0; a < M; a++)
		{
			if (g.host[a].name == UDHost[l])
			{
				l = ww(e);
				a = 0;
			}
		}
		q = g.host[k].name;//记录更改主机位置前的主机位置
		g.host[k].name = UDHost[l];

		Cmax = m.HostToHostCmax(g);
		if (Cbest > Cmax)
		{
			Cbest = Cmax;
			j = 0;
		}
		else
		{
			if (nn(e) < (int)((exp((Cbest - Cmax))) * T))
			{
				Cbest = Cmax;
				j++;
			}
			else
			{
				g.host[k].name = q;
				j++;
			}
		}
		if (j == 1000)
			i = 0;
		if (T>1)
			T--;
	}
	//g.host[0].name = 3;
	//g.host[1].name = 13;
	//g.host[2].name = 13;
	g.ShowHost();
	m.HostToHostCmax(g);
	m.ShowhostC(g);
	char w[20] = "degreeofhost.txt";
	ofstream fout(w, ios::out);
	for (int i = 0; i < M; i++)
	{
		fout << g.ReturnDeg(g.host[i].name) << " ";
	}
	fout.close();
	char w2[20] = "SAU(i).txt";
	MAXGeneratedPackets(100, m.HostToHostAverangeDistance(g), M, m.HostToHostCmax(g, w2, 1));
	//g.DFSTraverse(Visit);
	//m.ShowPC(0,1);
	//m.ShowPC(1,0);
}