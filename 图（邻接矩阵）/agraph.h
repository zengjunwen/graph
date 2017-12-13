//AGraph.hͼ������Ķ���
#ifndef _AGRAPH_H_
#define _AGRAPH_H_
#define big 10000000
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef int VRType;//���嶥���ϵ��Ȩֵ������Ϊ����
template<typename VerT>class AGraph
{
private:
		void DFS(int i, void(*visit)(VerT), bool Visited[])
	{//�Ӷ���[i]�����ݹ��������ȱ���ͼ��DFSTraverse()����
		Visited[i] = true;//���÷��ʱ�־Ϊtrue���ѷ��ʣ�
		visit(GetVex(i));//���ʶ���[i]
		for (int j = FirstAdjVex(i); j >= 0; j = NextAdjVex(i, j))
			//�Ӷ���[i]�ĵ�һ���ڽӶ���[j]��ʼ
			if (!Visited[j])//�ڽӶ���[j]δ������
				DFS(j, visit, Visited);
		//�Զ���[i]����δ���ʵ��ڽӶ���[j]�ݹ����DFS
	}
protected:
	int ArcNum;//ͼ�Ļ���
	bool Weight=0;//ture����Ȩ��false����Ȩ
	bool Directed=0;//ture������false������
public:
	void CreateFromFile(char* FileName);//�������ļ�FileName����ͼ
	void InsertVex(VerT v);//�����¶���v
	bool DeleteVex(VerT v);//ɾ������v������صĻ�
	bool InsertArc(VerT v,VerT w);//����<v,w>,���������Ļ�Ӧ�����<w,v>
	bool DeleteArc(VerT v,VerT w);//ɾ����<v,w>,���������Ļ�Ӧ��ɾ��<w,v>
	virtual int GetVexNumOrArcNum(int i)const = 0;//����ͼ�Ķ�������i=0��������i=1��
	virtual VerT GetVex(int i)const = 0;//���ض���[i]��ֵ
	virtual int FirstAdjVex(int i)const = 0;
	virtual int NextAdjVex(int i, int j)const = 0;
	void DFSTraverse(void(*visit)(VerT))
	{//�Ӷ���[0]��������ȵݹ����ͼ������ÿ��������ú���visitһ���ҽ�һ��
		int i;
		bool *Visited = new bool[GetVexNumOrArcNum(0)];
		for (i = 0; i<GetVexNumOrArcNum(0); i++)
			Visited[i] = false;
		for (i = 0; i<GetVexNumOrArcNum(0); i++)
			if (!Visited[i])
				DFS(i, visit, Visited);
		cout << endl;
		delete[]Visited;
	}
};

#endif