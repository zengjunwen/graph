void SetHost(int MAX_VERTEX_NUM_a, int M_b)
{
	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;
	char w[9] = "F5-w.txt";
	char r[14] = "p2p.txt";

	MatrixGraph<V, A> g;
	ShortestPath<V, A> m;

	g.CreateFromFile(r);
	g.RandomHost();
	g.host[0].name = 4482;
	g.host[1].name = 5386;
	g.host[2].name = 3348;
	g.host[3].name = 1417;
	g.host[4].name = 2261;
	g.host[5].name = 4260;
	g.host[6].name = 1295;
	g.host[7].name = 2879;
	g.host[8].name = 1907;
	g.host[9].name = 4900;

	g.ShowHost();
	m.HostCmax(g);
	m.ShowhostC(g);
}