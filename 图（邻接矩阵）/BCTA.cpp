//����������ȷ������λ��
void BCTA(MatrixGraph<V,A>&g, int hostnum)
{//�ڵ���֮ǰ����Ҫ���壨���еı����⻹Ҫ�ں����Ŀ�������Ҫ����д���ļ�r��w��
	g.HostNum = hostnum;
	ShortestPath<V, A>p;
	Betweenness<V, A> b;
	b.CountB(g);
	b.OrderBigToSmallB(g);
	for (int j = 0; j < M; j++)
	{//�������ж���ڵ����㶨λ
		for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
		{
			if (b.ReturnB(n) == b.ReturnOrderB(j))
			{//��λ�ڵ�
				int ture = 1;
				for (int k = 0; k < j; k++)
				{//��λ�Ľڵ��Ƿ��������д���
					if (g.host[k].name == n)
						ture = 0;
				}
				if (ture == 1)
				{//��λ�ڵ��������в�����
					g.host[j].name = n;
					//cout <<j<< n << endl;
				}
			}
		}
	}
	cout << "BCTA" << endl;
	g.ShowHost();
}