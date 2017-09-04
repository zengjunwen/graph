#ifndef _CLOSENESSCENTRALITY_H_
#define _CLOSENESSCENTRALITY_H_
int MyCompareOrderCC(const void * elem1, const void * elem2)
{//排序函数中的比较函数定义
	int * p1, *p2;
	p1 = (int *)elem1; // “ * elem1” 非法
	p2 = (int *)elem2; // “ * elem2” 非法
	return (*p2 - *p1);
}
template<typename VerT, typename ArcT>class ClosenessCentrality
{
private:
	float *CC = new float[MAX_VERTEX_NUM];
	float *OrderCC = new float[MAX_VERTEX_NUM];
public:
	ClosenessCentrality()
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			CC[i] = 0;
			OrderCC[i] = 0;
		}
	}
	ClosenessCentrality(const ClosenessCentrality&C)
	{
		for (int i = 0; i < MAX_VERTEX_NUM; i++)
		{
			CC[i] = C.CC[i];
			OrderCC[i] =C.OrderCC[i];
		}
	}
	~ClosenessCentrality()
	{
		delete[]CC;
		delete[]OrderCC;
		cout << "删除接近中心性动态数组和其排序数组！"<<endl;
	}
	void CountCC(MatrixGraph<VerT, ArcT>&G, ShortestPath<VerT, ArcT>&P)
	{
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{
			P.ShortestPath_DIJ(G, i);
				for (int j = 0; j < G.GetVexNumOrArcNum(0); j++)
				{
					CC[i] += P.ReturnD(j);
				}
			CC[i] = G.GetVexNumOrArcNum(0) / CC[i];
		}
	}
	float ReturnCC(int i)
	{
		return CC[i];
	}
	void ShowCC(int i)
	{
		cout << "第" << i << "个节点的接近中心性为：" << CC[i] << endl;
	}
	void OrderBigToSmallCC(MatrixGraph<VerT, ArcT>&G)
	{
		for (int i = 0; i < G.GetVexNumOrArcNum(0); i++)
		{//将CC[]复制到OrderCC[]中
			OrderCC[i] = CC[i];
		}
		qsort(OrderCC, G.GetVexNumOrArcNum(0), sizeof(float), MyCompareOrderCC);
	}
	float ReturnOrderCC(int i)
	{
		return OrderCC[i];
	}
	void ShowOrderCC(int i)
	{
		cout << "OrderCC[]中元素" << i << "的接近中心性为：" << OrderCC[i] << endl;
	}
};
#endif