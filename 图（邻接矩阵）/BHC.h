#ifndef _BHC_H_
#define _BHC_H_

template<typename VerT, typename ArcT>
class BHC
{
	int **DD;//����M����̾����
	int ***PP;
public:
	BHC()
	{
		DD = new int*[M];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
			DD[i] = new int[MAX_VERTEX_NUM]();//�����()�ܽ����ٵĶ�̬�����ʼ��Ϊ0��

		PP = new int**[M];
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			PP[i] = new int*[MAX_VERTEX_NUM];
			for (int j = 0; j <MAX_VERTEX_NUM; j++)
			{
				PP[i][j] = new int[MAX_VERTEX_NUM]();
			}
		}
	}
	~BHC()
	{
		//ɾ����صĶ�̬����
		for (int i = 0; i < M; i++)
		{
			delete[]DD[i];
		}
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j <MAX_VERTEX_NUM; j++)
			{
				delete[]PP[i][j];
			}
		}
	}
	int NearHostCmax(MatrixGraph<VerT, ArcT> &G, ShortestPath<VerT, ArcT> &PATH)
	{
		for (int i = 0; i < M; i++)
		{
			PATH.ShortestPath_DIJ(G, G.host[i].name);
			for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
			{
				DD[i][j] = PATH.D[j];
				for (int k = 0; k < G.GetVexNumOrArcNum(0); k++)
				{
					PP[i][j][k] = PATH.P[j][k];
				}
			}
		}
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
			PATH.C[i] = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			int TESTDD = DD[0][i];
			int NUMDD = 0;
			for (int j = 0; j < M; j++)
			{//�ó���i���������ĸ��������
				if (DD[j][i] < TESTDD)
				{
					TESTDD = DD[j][i];
					NUMDD = j;
				}
			}
			cout << "df" << NUMDD;
			for (int m = 0; m < G.GetVexNumOrArcNum(0); m++)
			{
				cout << PP[i][NUMDD][m];
				if (m != i&&m != NUMDD)
					PATH.C[m] = PATH.C[m] + PP[i][NUMDD][m];//��i���㵽�����j��ͨ���ĵ�
			}
		}
		int v;//���ʹ���ʵĵ�v������
		int total = 0;
		int max = 0;
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			total += PATH.C[i];
			if (max < PATH.C[i])
			{
				max = PATH.C[i];
				v = i;
			}
		}
		cout << "ͼ�����ڵ�ʹ�ø��ʺʹ�����" << (float)max / total << "  " << max << endl;
		cout << "���ʹ���ʽڵ�������:" << v << "  " << G.ReturnDeg(v) << endl;
		return max;
	}
	
};
#endif