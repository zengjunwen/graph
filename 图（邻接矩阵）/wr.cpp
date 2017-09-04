void wr(int MAX_VERTEX_NUM_a, int M_b)
{
	char w[9] = "F5-w.txt";
	char r[14] = "cel.txt";
	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;
	MatrixGraph<V, A> g;

	g.CreateFromFile(r);
	g.CreateToFile(w);
}