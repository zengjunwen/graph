
void OneByOneChoiceHost(MatrixGraph<V, A>&g, int hostnum)
{
	g.CountDegree();
	g.HostNum =1;
	g.host[0].name = 0;
	for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
	{
		if (g.ReturnDeg(g.host[0].name) < g.ReturnDeg(i))
			g.host[0].name = i;
	}
	vector<int> SET;
	vector<int>::iterator dele;
	vector<int> bian;
	vector<int>du;
	int bianmax;
	int biannum;
	int daidinghost;
	while (g.HostNum < hostnum)
	{
		for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
		{
			SET.push_back(i);
		}
		for (int i = 0; i < g.HostNum; i++)
		{
			dele = find(SET.begin(), SET.end(), g.host[i].name);
			SET.erase(dele);
		}
		for (int i = 0; i < SET.size();i++)
		{
			bian.push_back(0);
		}
		bianmax = 0;
		for (int i = 0; i < g.GetVexNumOrArcNum(0) - g.HostNum; i++)
		{
			biannum = 0;
			for (int j = 0; j < g.HostNum; j++)
			{
				if (g.arcs[SET[i]][g.host[j].name].adj == 1)
					biannum++;
			}
			bian[i] = biannum;
			if (bianmax < biannum)
				bianmax = biannum;
		}

		//留下和主机连边最多的节点
		for (int i = 0; i < SET.size(); i++)
		{
			if (bian[i] < bianmax)
			{
				SET.erase(SET.begin() + i);
				bian.erase(bian.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < SET.size(); i++)
		{
			du.push_back(0);
		}
		//选择度最大的点
		daidinghost = 0;
		for (int i = 0; i < SET.size(); i++)
		{
			for (int j = 0; j < g.GetVexNumOrArcNum(0); j++)
			{
				if (g.arcs[SET[i]][j].adj == 1)
					du[i]++;
			}
		}
		for (int i = 0; i < SET.size(); i++)
		{
			if (du[daidinghost] < du[i])
				daidinghost = i;
		}
		g.host[g.HostNum].name = SET[daidinghost];
		g.HostNum++;
		SET.clear();
		bian.clear();
		du.clear();
	}
	cout << "OneByOneChoiceHost" << endl;
	g.ShowHost();
}