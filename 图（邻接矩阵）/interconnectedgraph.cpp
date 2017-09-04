void Interconnected(int MAX_VERTEX_NUM_a, int M_b, int choice,float p)
{
	MAX_VERTEX_NUM = MAX_VERTEX_NUM_a;
	M = M_b;
	MatrixGraph<V, A>g1;
	MatrixGraph<V, A>g2;
	g1.CreateFromFile(r);
	g1.Sethost(host1);
	g2.CreateFromFile(rr);
	g2.Sethost(host2);
	InterconnectedGraph<V, A> GG(g1, g2);
	GG.ConnectedMethod(p,choice);
}