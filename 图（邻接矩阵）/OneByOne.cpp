int MyCompareOneByOne(const void * elem1, const void * elem2)
{
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p2 - *p1);
}
void OneByOne(int MAX_VERTEX_NUM_a, int M_b)
{
	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;


	MatrixGraph<V, A> g;
	ShortestPath<V, A> m;

	//g.BA();
	g.CreateFromFile(r);
	g.CreateToFile(w);
	int *an;
	an = new int[g.GetVexNumOrArcNum(0)];
	M = 1;
	for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
	{
		g.host[0].name = i;
		an[i] = m.HostCmax(g,0);
		//cout << an[i]<<endl;
	}
	qsort(an, g.GetVexNumOrArcNum(0), sizeof(int), MyCompareOneByOne);
	int copy;//备份第一个主机节点
	for (int j = 0; j < M_b; j++)
	{
		for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
		{
			g.host[0].name = n;
			if (m.HostCmax(g,0) == an[j])
			{
				if (j!=0)
					g.host[0].name = copy;//还原第一个主机节点
				int ture = 1;
				for (int k = 0; k < j; k++)
				{
					if (g.host[k].name == n)
						ture = 0;
				}
				if (ture == 1)
					g.host[j].name = n;
			}
		}
		if (j == 0)
			copy = g.host[0].name;
	}
	delete[]an;
	M = M_b;
	cout << "OneByOne:" << endl;
	g.ShowHost();
	MAXGeneratedPackets(100, m.HostToHostAverangeDistance(g), M, m.HostToHostCmax(g));
	//m.ShowhostC(g);
	//m.ShowPC(0,1);
	//m.ShowPC(1,0);
}