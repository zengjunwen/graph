void RTA(MatrixGraph<V, A>&g, int hostnum)
{
	g.HostNum = hostnum;
	cout << "RTA" << endl;
	g.RandomHost();
	g.ShowHost();
}
	