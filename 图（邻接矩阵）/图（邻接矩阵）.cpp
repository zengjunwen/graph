// 图（邻接矩阵）.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
int MAX_VERTEX_NUM = 500;
int M = 500;
#include "MatrixGraph.h"
#include"ShortestPath.h"
#include"InterconnectedGraph.h"
#include"Betweenness.h"
#include"ClosenessCentrality.h"
#include"V.cpp"
#include"ctime"
#include<algorithm>
#include"string"

char w[9] = "F5-w.txt";
//char r[14] = "test.txt";
string r;
//char r[30] = "kite.txt";
char rr[20] = "BA(300-2)_2.txt";
char host[20] = "host3.txt";
char host1[20] = "host1.txt";
char host2[20] = "host2.txt";
//char r[14] = "BA(300-2).txt";

//#include"wr.cpp"
//#include"k-core.cpp"
#include"maxgeneratedpackets.cpp"
#include"RTA.cpp"
#include"SA.cpp"
#include"CTA.cpp"
//#include"OneByOne.cpp"
#include"DTA.cpp"
#include"CCTA.cpp"
#include"BCTA.cpp"
#include"OneByOneChoiceHost.cpp"
//#include"interconnectedgraph.cpp"
//#include"LDSA.cpp"
float TotalD,TotalUmax,TotalCmax,TotalS, TotalSS, Totalxiaos,TotalE;
#include"failure.cpp"
//#include"SetHost.cpp"

int _tmain(int argc, _TCHAR* argv[])
{
	clock_t start_time = clock();//记录计算开始时间
	
	{
		ofstream eout("HostToHostEfficiency.txt", ios::out);
		ofstream sout("xiaos.txt", ios::out);
		ofstream Sout("S.txt", ios::out);
		ofstream Uout("Umax.txt", ios::out);
		ofstream Cout("Cmax.txt", ios::out);
		ofstream Dout("HostToHostDistance.txt", ios::out);
		ofstream SSout("SS.txt", ios::out);
		SSout.close();
		Dout.close();
		Cout.close();
		Uout.close();
		sout.close();
		Sout.close();
		eout.close();
	}

	MatrixGraph<V, A>g;
	ShortestPath<V, A>p,p2;
	M = 500*0.25;
	for (int a = 0; a <= 20; a++)
	{
		for (int b = 0; b <= 20; b++)
		{
			TotalD = TotalUmax = TotalCmax = 0;
			TotalS = TotalSS = Totalxiaos = TotalE = 0;
			for (int i = 1; i <= 20; i++)
			{
				r = "./BA/" + to_string(i) + "BA.txt";
				g.CreateFromFile(r);

				int AveNum1 = 1, AveNum2 = 1;
				p.Countallshortpath(g);

				g.CountDegree();
				for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
				{
					g.ChangeGen(i, 1);
				}
				DTA(g, M, 1);

				//CTA(g, p, M);
				//RTA(g, M);
				//CCTA(g, M);
				//BCTA(g,100);
				//SA(g, 200);
				//g1.OutputHost("BAhost.txt");
				//OneByOneChoiceHost(g,M);
				float HostToHostE = p.HostToHostEfficiency(g);
				TotalD += p.HostToHostAverangeDistance(g);
				TotalUmax += p.ReturnUmax();
				TotalCmax += p.ReturnCmax();


				for (int i = 0; i < g.GetVexNumOrArcNum(0); i++)
				{
					g.ChangeCap(i, (1+0.05*a)*p.ReturnC(i));
					//cout << p.ReturnC(i) << "  " << g.returnCap(i) << endl;
				}
				for (int i = 0; i < g.HostNum; i++)
				{
					g.ChangeCap(g.host[i].name, (1 + 0.05*b)*p.ReturnC(g.host[i].name));
					//cout << p.ReturnC(i) << "  " << g.returnCap(i) << endl;
				}

				p2.HostToHostAverangeDistance(g);
				for (int a = 0; a < 1; a++)
				{
					for (int j = 0; j < AveNum1; j++)//放置主机次数
					{
						/*TotalD +=p.HostToHostAverangeDistance(g);
						TotalUmax += p.ReturnUmax();
						TotalCmax += p.ReturnCmax();
						cout<< p.ReturnCmax() << endl;*/
						//if (p2.ReturnC(a) != 0)
						//{
						failure(g, p, 1.2, 3, 1, a);
						TotalE += p.HostToHostEfficiency(g);
						g.DestroyGraph();
						g.CreateFromFile(r);
						//}
						//else
						//{
						//	TotalS = 1;
						//	Totalxiaos = M;
						//	TotalE = HostToHostE;

						//}
					}
					g.CreateFromFile(r);
				}
			}
			ofstream Dout("HostToHostDistance.txt", ios::app);
			Dout << TotalD / 20 << " ";
			Dout.close();
			ofstream Uout("Umax.txt", ios::app);
			Uout << TotalUmax / 20 << " ";
			Uout.close();
			ofstream Cout("Cmax.txt", ios::app);
			Cout << TotalCmax / 20 << " ";
			Cout.close();
			ofstream sout("xiaos.txt", ios::app);
			sout << (float)Totalxiaos / 20 << " ";
			sout.close();
			ofstream Sout("S.txt", ios::app);
			Sout << (float)TotalS / 20 << " ";
			Sout.close();
			ofstream eout("HostToHostEfficiency.txt", ios::app);
			eout << (float)TotalE / 20 << " ";
			eout.close();
		}
	}
	clock_t end_time = clock();//记录计算结束时间
	cout<< "计算时间为：" << end_time - start_time << "ms"<<endl;
	while (1);
	return 0;
}

