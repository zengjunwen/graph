//基于接近中心性确定主机位置
void CCTA(MatrixGraph<V,A>&g, int hostnum)
{//在调用之前出来要定义（）中的变量外还要在函数的看到设置要读和写的文件r，w。
	g.HostNum = hostnum;
	ShortestPath<V, A>p;
	ClosenessCentrality<V, A> cc;
	cc.CountCC(g, p);
	cc.OrderBigToSmallCC(g);
	for (int j = 0; j < M; j++)
	{//适用于有多个节点满足定位
		for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
		{
			if (cc.ReturnCC(n) == cc.ReturnOrderCC(j))
			{//定位节点
				int ture = 1;
				for (int k = 0; k < j; k++)
				{//定位的节点是否在主机中存在
					if (g.host[k].name == n)
						ture = 0;
				}
				if (ture == 1)
				{//定位节点在主机中不存在
					g.host[j].name = n;
					//cout <<j<< n << endl;
				}
			}
		}
	}
	cout << "CCTA" << endl;
	g.ShowHost();
}