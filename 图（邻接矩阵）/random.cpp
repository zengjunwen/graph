MatrixGraph<Vint, A>g;
int i, j;
float f;
void Random()
{
	int  p;
	Vint v;
	v.name = 1;
	//cout << "输入顶点数：";
	//cin >> i;
	//cout << endl;
	j = i;
	//cout << "输入链接概率：";
	//cin >> f;
	//f = 0.6;
	p = f * 1000;
	for (i; i > 0; i--)
	{
		g.InsertVex(v);
		v.name++;
	}
	i = j;

	for (j; j > 0; j--)
	{
		i = j - 1;
		for (i; i > 0; i--)
			if (rand() % 1000<p)
			{
				g.InsertArc(g.vexs[i - 1], g.vexs[j - 1]);
			}
	}

}