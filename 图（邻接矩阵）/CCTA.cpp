//���ڽӽ�������ȷ������λ��
void CCTA(MatrixGraph<V,A>&g, int hostnum)
{//�ڵ���֮ǰ����Ҫ���壨���еı����⻹Ҫ�ں����Ŀ�������Ҫ����д���ļ�r��w��
	g.HostNum = hostnum;
	ShortestPath<V, A>p;
	ClosenessCentrality<V, A> cc;
	cc.CountCC(g, p);
	cc.OrderBigToSmallCC(g);
	for (int j = 0; j < M; j++)
	{//�������ж���ڵ����㶨λ
		for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
		{
			if (cc.ReturnCC(n) == cc.ReturnOrderCC(j))
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
	cout << "CCTA" << endl;
	g.ShowHost();
}