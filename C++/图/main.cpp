#include <iostream>
#include "Graph.h"

void TestGraph1()
{
	Graph<char, int, INT_MAX, true> g("0123", 4);
	g.AddEdge('0', '1', 1);
	g.AddEdge('0', '3', 4);
	g.AddEdge('1', '3', 2);
	g.AddEdge('1', '2', 9);
	g.AddEdge('2', '3', 8);
	g.AddEdge('2', '1', 5);
	g.AddEdge('2', '0', 3);
	g.AddEdge('3', '2', 6);
	g.Print();

}

void TestGraph2()
{
	string a[] = { "����", "����", "����", "����", "����" };
	Graph<string, int> g1(a, sizeof(a)/sizeof(a[0]));
	g1.AddEdge("����", "����", 1);
	g1.AddEdge("����", "����", 2);
	g1.AddEdge("����", "����", 3);
	g1.AddEdge("����", "����", 7);
	g1.Print();

	g1.BFS("����");
	g1.DFS("����");

	Graph<string, int> g2;
}

void TestGraphMinTree()
{
	const char* str = "abcdefghi";
	Graph<char, int> g(str, strlen(str));
	g.AddEdge('a', 'b', 4);
	g.AddEdge('a', 'h', 8);
	//g.AddEdge('a', 'h', 9);
	g.AddEdge('b', 'c', 8);
	g.AddEdge('b', 'h', 11);
	g.AddEdge('c', 'i', 2);
	g.AddEdge('c', 'f', 4);
	g.AddEdge('c', 'd', 7);
	g.AddEdge('d', 'f', 14);
	g.AddEdge('d', 'e', 9);
	g.AddEdge('e', 'f', 10);
	g.AddEdge('f', 'g', 2);
	g.AddEdge('g', 'h', 1);
	g.AddEdge('g', 'i', 6);
	g.AddEdge('h', 'i', 7);
	//Graph<char, int> kminTree;
	//cout << "Kruskal:" << g.Kruskal(kminTree) << endl;
	//kminTree.Print();
	Graph<char, int> pminTree;
	cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
	pminTree.Print();
}

void TestGraphDijkstra()
{
	const char* str = "syztx";
	Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 10);
	g.AddEdge('s', 'y', 5);
	g.AddEdge('y', 't', 3);
	g.AddEdge('y', 'x', 9);
	g.AddEdge('y', 'z', 2);
	g.AddEdge('z', 's', 7);
	g.AddEdge('z', 'x', 6);
	g.AddEdge('t', 'y', 2);
	g.AddEdge('t', 'x', 1);
	g.AddEdge('x', 'z', 4);
	
	vector<int> dist;
	vector<int> parentPath;
	g.Dijkstra('s', dist, parentPath);
	g.PrinrtShotPath('s', dist, parentPath);
	// ͼ�д��и�Ȩ·��ʱ��̰�Ĳ�����ʧЧ�ˡ�
	// ���Խ�����Կ���s->t->y֮������·��û���³���
	/*const char* str = "sytx";
	 Graph<char, int, INT_MAX, true> g(str, strlen(str));
	 g.AddEdge('s', 't', 10);
	 g.AddEdge('s', 'y', 5);
	 g.AddEdge('t', 'y', -7);
	 g.AddEdge('y', 'x', 3);
	 vector<int> dist;
	 vector<int> parentPath;
	 g.Dijkstra('s', dist, parentPath);
	 g.PrinrtShotPath('s', dist, parentPath);*/
}

void TestGraphBellmanFord()
{
	const char* str = "syztx";
	Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('s', 't', 6);
	g.AddEdge('s', 'y', 7);
	g.AddEdge('y', 'z', 9);
	g.AddEdge('y', 'x', -3);
	g.AddEdge('z', 's', 2);
	g.AddEdge('z', 'x', 7);
	g.AddEdge('t', 'x', 5);
	g.AddEdge('t', 'y', 8);
	g.AddEdge('t', 'z', -4);
	g.AddEdge('x', 't', -2);
	vector<int> dist;
	vector<int> parentPath;
	if (g.BellmanFord('s', dist, parentPath))
	{
		g.PrinrtShotPath('s', dist, parentPath);
	}
	else
	{
		cout << "���ڸ�Ȩ��·" << endl;
	}
	// ΢��ͼ�ṹ�����и�Ȩ��·�Ĳ���
	//const char* str = "syztx";
	//Graph<char, int, INT_MAX, true> g(str, strlen(str));
	//g.AddEdge('s', 't', 6);
	//g.AddEdge('s', 'y', 7);
	//g.AddEdge('y', 'x', -3);
	//g.AddEdge('y', 'z', 9);
	//g.AddEdge('y', 'x', -3);
	//g.AddEdge('y', 's', 1); // ����
	//g.AddEdge('z', 's', 2);
	//g.AddEdge('z', 'x', 7);
	//g.AddEdge('t', 'x', 5);
	//g.AddEdge('t', 'y', -8); // ����
	//g.AddEdge('t', 'z', -4);
	//g.AddEdge('x', 't', -2);
	//vector<int> dist;
	//vector<int> parentPath;
	//if (g.BellmanFord('s', dist, parentPath))
	//{
	// g.PrinrtShotPath('s', dist, parentPath);
	//}
	//else
	//{
	// cout << "���ڸ�Ȩ��·" << endl;
	//}
}

void TestFloydWarShall()
{
	const char* str = "12345";
	Graph<char, int, INT_MAX, true> g(str, strlen(str));
	g.AddEdge('1', '2', 3);
	g.AddEdge('1', '3', 8);
	g.AddEdge('1', '5', -4);
	g.AddEdge('2', '4', 1);
	g.AddEdge('2', '5', 7);
	g.AddEdge('3', '2', 4);
	g.AddEdge('4', '1', 2);
	g.AddEdge('4', '3', -5);
	g.AddEdge('5', '4', 6);
	vector<vector<int>> vvDist;
	vector<vector<int>> vvParentPath;
	g.FloydWarShall(vvDist, vvParentPath);
	// ��ӡ��������֮������·��
	for (size_t i = 0; i < strlen(str); ++i)
	{
		g.PrinrtShotPath(str[i], vvDist[i], vvParentPath[i]);
		cout << endl;
	}
}


int main()
{
	std::cout << "hello" << std::endl;

	//TestGraph1();
	//TestGraph2();
	//TestGraphMinTree();
	//TestGraphDijkstra();
	//TestGraphBellmanFord();
	TestFloydWarShall();

	return 0;
}