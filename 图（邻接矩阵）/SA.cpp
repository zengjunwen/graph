/*形参w为存储图的文件的名字所在数组，注意对图的要求（是否有节点的标号），该函数会将退火过程中的Cbest写入到asCbest.txt中，会把主机的度写入degreeofhost.txt中，会把负载分配写入SAU(i).txt中*/
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
	ofstream fout(saCbest, ios::out);//输出图到文件并删除原来文件的内容
	m.Countallshortpath(g);
	int step = 0;
	while (i)
	{

		//随机选一个节点做为主机节点
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
		q = g.host[k].name;//记录更改主机位置前的主机位置
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