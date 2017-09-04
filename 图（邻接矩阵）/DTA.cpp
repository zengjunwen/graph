#include"random"
#include"ctime"

int MyCompare2(const void * elem1, const void * elem2)
{
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p2 - *p1);
}
void DTA(MatrixGraph<V, A> &g, int hostnum, int choice)
{
	g.HostNum = hostnum;
	int *an = new int[g.GetVexNumOrArcNum(0)];
	g.CountDegree();
	for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
	{
		an[i] = g.ReturnDeg(i);
		//cout << an[i]<<endl;
	}

	int i = 1, j = 0, k, l, q;
	qsort(an, g.GetVexNumOrArcNum(0), sizeof(int), MyCompare2);
	switch (choice){
	case 1:
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
						//cout << n << endl;
					}
				}
			}
		}
		cout << "HDTA" << endl;
		g.ShowHost();
		break;
	case 2:
		for (int j = M; j > 0; j--)
		{
			for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
			{
				if (g.ReturnDeg(n) == an[g.GetVexNumOrArcNum(0) - M + j - 1])
				{
					int ture = 1;
					for (int k = 0; k < M - j; k++)
					{
						if (g.host[k].name == n)
							ture = 0;
					}
					if (ture == 1)
					{
						g.host[M - j].name = n;
						//cout << n << endl;
					}
				}
			}
		}
		cout << "LDTA" << endl;
		g.ShowHost();
		break;
	default: cout << "errow";
	}
	delete an;
}