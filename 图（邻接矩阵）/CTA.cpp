#include"random"
#include"ctime"

int MyCompare(const void * elem1, const void * elem2)
{
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p2 - *p1);
}
void CTA(MatrixGraph<V, A>&g,ShortestPath<V,A>&p, int hostnum)
{
	p.CoutNoedToNodeC(g);//在计算所有最短路径的前提下，计算每个点的使用次数
	g.HostNum = hostnum;
	int *an;
	an = new int[g.GetVexNumOrArcNum(0)];
	for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
	{
		an[i] = p.ReturnC(i);
	}
	qsort(an, g.GetVexNumOrArcNum(0), sizeof(int), MyCompare);
	for (int j = 0; j < M; j++)
	{
		for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
		{
			if (p.ReturnC(n) == an[j])
			{
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
	}
	cout << "CTA" << endl;
	g.ShowHost();
}