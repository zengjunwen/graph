//capΪ���ýڵ��ͨ��������attackΪ����Ŀ�����࣬��ֵΪ1ʱΪ�����������ֵΪ2��3ʱΪ��Ŀ�ĵĹ���,Ϊ4ʱ����removeNode�ڵ㣬fΪ�Ƴ��ڵ�����
void failure(MatrixGraph<V, A>&g, ShortestPath<V, A>&p,float cap,int attack,int f,int removeNode=0)
{
	cout << endl << "����ʧЧ�׶�..." << endl;
	//p.Countallshortpath(g);
	//p.HostToHostAverangeDistance(g);
	//p.CoutNoedToNodeC(g);
	/*for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
	{
		g.ChangeCap(i, cap*p.ReturnC(i));
		//cout << p.ReturnC(i) << "  " << g.returnCap(i) << endl;
	}*/

	vector<vector<int>> G,GG;//����ʧЧ�����ͼ
	vector<int> G1;
	vector<int> G2;
	int Distance_total;

	for (int i = 0; i < M; i++)
	{
		G1.push_back(g.host[i].name);
	}

	uniform_int_distribution<unsigned> uu(0, g.GetVexNumOrArcNum(0)-1);
	default_random_engine e(time(0));
	vector<int> FNode;
	int T = 1;
	switch (attack)
	{
		int Unsure;
	case 1:
		for (int i = 0; i < f; i++)
		{
			int back=1;
			Unsure = uu(e);
			vector<int>::iterator result = find(FNode.begin(), FNode.end(), Unsure);
			while (back)
			{
				if (result==FNode.end())
				{
					FNode.push_back(Unsure);
					back = 0;
				}
				else
				{
					Unsure = uu(e);
					result = find(FNode.begin(), FNode.end(), Unsure);
				}
			}
		}
		cout << "����������Ľڵ�Ϊ��";
		for (int i = 0; i < f; i++)
		{
			cout << FNode.back()<<endl;
			g.DeleteArcsOfVex(FNode.back());
			FNode.pop_back();
		}
		break;
	case 2:
	{
		int *an = new int[g.GetVexNumOrArcNum(0)];
		int *DelHost = new int[f];
		g.CountDegree();
		for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
		{
			an[i] = g.ReturnDeg(i);
		}
		qsort(an, g.GetVexNumOrArcNum(0), sizeof(int), MyCompare2);
		for (int j = 0; j < f; j++)
		{
			for (int n = 0; n < g.GetVexNumOrArcNum(0); n++)
			{
				if (g.ReturnDeg(n) == an[j])
				{
					int ture = 1;
					for (int k = 0; k < j; k++)
					{
						if (DelHost[k] == n)
							ture = 0;
					}
					if (ture == 1)
					{
						DelHost[j] = n;
						//cout << n << endl;
					}
				}
			}
		}
		cout << "�����⹥���Ľڵ�Ϊ��";
		for (int i = 0; i < f; i++)
		{
			cout << DelHost[i] << " ";
			g.DeleteArcsOfVex(DelHost[i]);
		}
		cout <<endl;
		//FNode = p.HostToHostCmax(g, NULL,0,0);
		//g.DeleteArcsOfVex(FNode);
		//cout << "�����⹥���Ľڵ�Ϊ��" << FNode << endl;
		delete DelHost;
		delete an;
	}
		break;
	case 3:
	{
		cout << "�����⹥���Ľڵ�Ϊ��";
		p.HostToHostAverangeDistance(g,0);
		int a = p.ReturnCmaxNode();
		cout << a << " ";
		g.DeleteArcsOfVex(a);
		cout << endl;
	}
	break;
	case 4:
	{
		cout << "�������Ľڵ�Ϊ��";
		cout << removeNode << " ";
		g.DeleteArcsOfVex(removeNode);
		cout << endl;
	}
	break;
	default:cout << "���빥�����ͳ���";
	}
		
		//g.Display();
		/*����ɾ��*/
		while (T == 1)
		{
			T = 0;
			int excess = 0;
			vector<int> UndeteSetVec;//��ɾ�㼯��

			UndeteSetVec.clear();
			p.HostToHostAverangeDistance(g);
			for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
			{
				if (p.ReturnC(i) > g.returnCap(i))
				{
					if (excess < p.ReturnC(i) - g.returnCap(i))
					{
						excess = p.ReturnC(i) - g.returnCap(i);
						UndeteSetVec.clear();
						UndeteSetVec.push_back(i);
					}
					if (excess = p.ReturnC(i) - g.returnCap(i))
					{
						UndeteSetVec.push_back(i);
					}
				}
			}
			if (UndeteSetVec.size() != 0)
			{
				T = 1;
				for (int i = 0; i < UndeteSetVec.size(); i++)
				{
					g.DeleteArcsOfVex(UndeteSetVec[i]);
				}
			}
		}

		//g.Display();

		/*�ҳ����к�����������ͼ���������������Ϸ���vector<vector<int>>G��*/
		while (G1.size() != 0)
		{
			p.ShortestPath_DIJ(g, G1[0]);
			for (int i = 1; i < G1.size(); i++)
			{
				if (p.ReturnD(G1[i]) == big)
				{//û��������g.host[i].name����
					G2.push_back(G1[i]);
					G1.erase(G1.begin() + i);
					i--;//���ڲ�������ǰ��
				}
			}
			G.push_back(G1);
			G1 = G2;
			G2.clear();
		}

		/*��������������ľ����ܺͷ���G��ÿ��Ԫ�ص�ĩβ*/
		for (int i = 0; i < G.size(); i++)
		{
			Distance_total = 0;
			for (int j = 0; j < G[i].size(); j++)
			{
				p.ShortestPath_DIJ(g, G[i][j]);
				for (int m = 0; m < G[i].size(); m++)
				{
					Distance_total += p.ReturnD(G[i][m]);
				}
			}
			G[i].push_back(Distance_total);//��G1��ĩβ������ͼG1�������������ľ����ܺ͡�
		}

		for (int i = 0; i < G.size(); i++)
		{
			for (int j = 0; j < G[i].size(); j++)
			{
				cout << G[i][j] << " ";
			}
			cout << endl;
		}




		for (int i = 0; i <g.GetVexNumOrArcNum(0); i++)
		{
			G1.push_back(i);
		}
		/*�ҳ�������ͼ������vector<vector<int>>GG��*/
		while (G1.size() != 0)
		{
			p.ShortestPath_DIJ(g, G1[0]);
			for (int i = 1; i < G1.size(); i++)
			{
				if (p.ReturnD(G1[i]) == big)
				{//û��������g.host[i].name����
					G2.push_back(G1[i]);
					G1.erase(G1.begin() + i);
					i--;//���ڲ�������ǰ��
				}
			}
			GG.push_back(G1);
			G1 = G2;
			G2.clear();
		}
		int NumMax = 0;
		for (int i = 0; i < GG.size(); i++)
		{
			if (NumMax < GG[i].size())
			{
				NumMax = GG[i].size();
			}
		}
		TotalSS += (float)NumMax / g.GetVexNumOrArcNum(0);

		Totalxiaos += (float)g.HostNum / G.size();
		cout << "<s>:" <<(float)g.HostNum/G.size()<< endl;
		
		int HostNumMax = 0;
		float RateMax = 0, distance = 0;
		
			for (int i = 0; i < G.size(); i++)
			{
				if (HostNumMax < G[i].size() - 1)
				{
					HostNumMax = G[i].size() - 1;
					RateMax = (float)(G[i].size() - 1) / g.HostNum;
					distance = (float)G[i][G[i].size() - 1] / (G[i].size() - 1) / (G[i].size() - 2);
				}
				//fout << G[i].size() - 1 << " " << (float)(G[i].size() - 1) / g.HostNum << " " << (float)G[i][G[i].size() - 1] / (G[i].size() - 1) / (G[i].size() - 2) << endl;
			}
			cout << "�����ͨ��ͼ������������������������ƽ�����룺" << endl;
			cout << HostNumMax << " " << RateMax << " " << distance << endl;
			TotalS += RateMax;
}