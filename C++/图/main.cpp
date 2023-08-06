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
	string a[] = { "张三", "李四", "王五", "赵六", "周七" };
	Graph<string, int> g1(a, sizeof(a)/sizeof(a[0]));
	g1.AddEdge("张三", "李四", 1);
	g1.AddEdge("张三", "王五", 2);
	g1.AddEdge("王五", "赵六", 3);
	g1.AddEdge("王五", "周七", 7);
	g1.Print();

	g1.BFS("张三");
	g1.DFS("张三");

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


int main()
{
	std::cout << "hello" << std::endl;

	//TestGraph1();
	//TestGraph2();
	TestGraphMinTree();

	return 0;
}