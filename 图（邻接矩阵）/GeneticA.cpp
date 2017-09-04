int MyCompareGeneticA(const void * elem1, const void * elem2)
{//排序函数中的比较函数定义
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p2 - *p1);
}
void GeneticA(int MAX_VERTEX_NUM_a, int M_b)
{
	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;

	MatrixGraph<V, A> g;
	ShortestPath<V, A> m;

	g.CreateFromFile(r);
	//g.CountDegree(1);
	//m.AverangeDistance(g);
	//m.MaxURN(g);
	//g.RandomHost();
	//g.ShowHost();
	//g.CreateToFile(w);
	int **A, **B;
	A = new int*[2 * M];
	B = new int*[2 * M];
	for (int i = 0; i < 2*M; i++)
	{
		A[i] = new int[MAX_VERTEX_NUM + 1];
		B[i] = new int[MAX_VERTEX_NUM + 1];
		A[i][0] = 1;
	}

	uniform_int_distribution<unsigned> nn(1, MAX_VERTEX_NUM);
	default_random_engine e(time(0));

	//initial
	int k;
	for (int j = 0; j < M; j++)
	{
		for (int i = 0; i < M; i++)
		{
			k = nn(e);
			while(A[j][k] == 1)
				k = nn(e);
			A[j][k] =A[M+j][k]= 1;
		}
	}

		//crossover
		int cross;
		for (int i = 0; i < M / 2; i++)
		{
			k = 1;
			int l = MAX_VERTEX_NUM + 1;
			for (int num = 0; num <2; num++)
			{
				for (int j = k; j < MAX_VERTEX_NUM + 1; j++)
				{
					if ((A[i * 2][k] ==1)&&( A[i * 2 + 1][k]!=1))
					{
						j = MAX_VERTEX_NUM + 1;
					}
					k++;
				}
				cross = A[i * 2][k-1];
				A[i * 2][k-1] = A[i * 2 + 1][k-1];
				A[i * 2 + 1][k-1] = cross;

				for (int j = l; j >1; j--)
				{
					l--;
					if (A[i * 2][l] !=1&& A[i * 2 + 1][l]==1)
					{
						j = 1;
					}
				}
				cross = A[i * 2][l];
				A[i * 2][l] = A[i * 2 + 1][l];
				A[i * 2 + 1][l] = cross;
			}
		}
		//variation  一定有一个基因变异
		/*for (int i = 0; i < M; i++)
		{
			k = nn(e);
			while(A[i][k]!= 1)
				k = nn(e);
				A[i][k] = 0;
				k = nn(e);
				while (A[i][k] == 1)
					k = nn(e);
				A[i][k] = 1;
		}*/
		//value
		float *V=new float[2*M];
		int Host;
		for (int i = 0; i < 2*M; i++)
		{
			Host = 0;
			for (int j = 0; j < MAX_VERTEX_NUM; j++)
			{
				if (A[i][j + 1] == 1)
				{
					g.host[Host].name = j;
					cout << j<<"  ";
					Host++;
				}
			}
			V[i] = MAXGeneratedPackets(100, m.HostToHostAverangeDistance(g), M, m.HostToHostCmax(g, NULL, 1, 1, 1));
			for (int k = 0; k < M; k++)
			{
				g.host[k].name = 0;
			}
		}

		//iteration
		int iterNUM = 100;
		float *aa=new float[2 * M];
		while (iterNUM--)
		{
			for (int i = 0; i < 2 * M; i++)
				aa[i] = V[i];
			qsort(aa, 2*M, sizeof(float), MyCompareGeneticA);
			//choice
			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < 2 * M; j++)
				{
					if (aa[i] == V[j] && A[j][0] == 1)
					{
						for (int m = 0; m < MAX_VERTEX_NUM + 1; m++)
							B[i][m] = A[j][m];
						A[j][0] == 0;
					}
				}
			}

			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < MAX_VERTEX_NUM + 1;j++)
					A[i][j] = B[i][j];
			}

			//crossover
			for (int i = 0; i < M / 2; i++)
			{
				k = 1;
				int l = MAX_VERTEX_NUM + 1;
				for (int num = 0; num <2; num++)
				{
					for (int j = k; j < MAX_VERTEX_NUM + 1; j++)
					{
						if ((A[i * 2][k] == 1) && (A[i * 2 + 1][k] != 1))
						{
							j = MAX_VERTEX_NUM + 1;
						}
						k++;
					}
					cross = A[i * 2][k - 1];
					A[i * 2][k - 1] = A[i * 2 + 1][k - 1];
					A[i * 2 + 1][k - 1] = cross;

					for (int j = l; j >1; j--)
					{
						l--;
						if (A[i * 2][l] != 1 && A[i * 2 + 1][l] == 1)
						{
							j = 1;
						}
					}
					cross = A[i * 2][l];
					A[i * 2][l] = A[i * 2 + 1][l];
					A[i * 2 + 1][l] = cross;
				}
			}
			//variation  一定有一个基因变异
			for (int i = 0; i < M; i++)
			{
			k = nn(e);
			while(A[i][k]!= 1)
			k = nn(e);
			A[i][k] = 0;
			k = nn(e);
			while (A[i][k] == 1)
			k = nn(e);
			A[i][k] = 1;
			}
			//value
			for (int i = 0; i < 2 * M; i++)
			{
				Host = 0;
				for (int j = 0; j < MAX_VERTEX_NUM; j++)
				{
					if (A[i][j + 1] == 1)
					{
						g.host[Host].name = j;
						cout << j << "  ";
						Host++;
					}
				}
				V[i] = MAXGeneratedPackets(100, m.HostToHostAverangeDistance(g), M, m.HostToHostCmax(g, NULL, 1, 1, 1));
				for (int k = 0; k < M; k++)
				{
					g.host[k].name = 0;
				}
			}
		}
}
