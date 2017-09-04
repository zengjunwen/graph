#include"random"
#include"ctime"

int MyCompare2(const void * elem1, const void * elem2)
{
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p2 - *p1);
}

void k_coreAD(int MAX_VERTEX_NUM_a, int M_b)
{

	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;
	//char r[14] = "BA(300-2).txt";
	//char r[9] = "exam.txt";
	MatrixGraph<V, A> g;
	ShortestPath<V, A> m;

	g.CreateFromFile(r);
	g.CreateToFile(w);
	
	V *UDHost = new V[g.GetVexNumOrArcNum(0)];
	g.K_CORE(1);
	cout << endl<< g.GetVexNumOrArcNum(0) << endl;
	g.CopyVexs(UDHost);
	
	g.DFSTraverse(Visit);

		

	int *an = new int[g.GetVexNumOrArcNum(0)];
	for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
	{
		an[i] = g.ReturnDeg(i);
		//cout << an[i]<<endl;
	}

	int i = 1, j = 0, k, l, q;
	qsort(an, g.GetVexNumOrArcNum(0), sizeof(int), MyCompare2);
	for (int j = 0; j < M; j++)
	{
		for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
		{
			if (g.ReturnDeg(n) == an[j])
			{
				int ture = 1;
				for (int k = 0; k < j; k++)
				{
					if (g.host[k].name == n)
						ture = 0;
				}
				if (ture == 1)
				{
					g.host[j].name = n;
					cout << n << endl;
				}
			}
		}
	}
	g.CreateFromFile(r);

	g.ShowHost();
	m.HostCmax(g);
	
}

void k_coreSA(int MAX_VERTEX_NUM_a, int M_b,int k_core_c)
{//基于k-core的模拟退火

	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;
	
	MatrixGraph<V, A> g;
	ShortestPath<V, A> m;

	g.CreateFromFile(r);
	

	g.K_CORE(k_core_c);
	g.CreateToFile(w);
	V *UDHost = new V[g.GetVexNumOrArcNum(0)];
	g.CopyVexs(UDHost);//复制主机待选节点
	int UDHostNum = g.GetVexNumOrArcNum(0);
	cout <<endl<<"节点个数" << g.GetVexNumOrArcNum(0)<<endl;
	g.DFSTraverse(Visit);
	//g.Display();

	g.CreateFromFile(r);
	if (1)
	{
		g.CountDegree();
		//m.AverangeDistance(g);
		//m.MaxURN(g);
		g.RandomHost();
		g.ShowHost();


		int Cbest, Cmax;
		int i = 1, j = 0, k, l, q, T = 10000;
		Cmax = m.HostCmax(g);
		Cbest = Cmax;

		uniform_int_distribution<unsigned> uu(0, M - 1);
		uniform_int_distribution<unsigned> ww(0, UDHostNum-1);
		uniform_int_distribution<unsigned> nn(0, 10000);
		default_random_engine e(time(0));
		while (i)
		{

			//随机选一个节点做为主机节点
			k = uu(e);
			l = ww(e);
			for (int a = 0; a < M; a++)
			{
				if (g.host[a].name == UDHost[l].name)
				{
					l= ww(e);
					a = 0;
				}
			}
			q = g.host[k].name;//记录更改主机位置前的主机位置
			g.host[k].name = UDHost[l].name;

			Cmax = m.HostCmax(g);
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
					j ++;
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
		g.ShowHost();
		m.HostCmax(g);
		m.ShowhostC(g);
		//g.DFSTraverse(Visit);
	}
}