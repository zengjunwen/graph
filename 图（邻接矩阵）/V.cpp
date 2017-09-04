struct V
{
	int name;
	float Cap;
	float Gen;
};
void Visit(V ver)
{//与之配套的访问节点函数
	cout << ver.name<<' ';
}
struct A
{
	int adj;
};
void InputVertex(V &ver)
{
	cin >> ver.name;
}
void InputVertexFromFile(ifstream &f, V &ver)
{
	f >> ver.name;
}
void InputVertexNameFromFile(ifstream &f, V &ver)
{
	f >> ver.name;
}

void InputArc(A &arc)
{
}
void OutputArc(bool direct, V ver1, V ver2, A arc)
{
}
void InputArcFromFile(ifstream &f, A &arc)
{
}
