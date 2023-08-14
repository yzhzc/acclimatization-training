#include <iostream>
#include "BTree.h"


using namespace std;

void TestBTree()
{
	int a[] = { 53, 139, 75, 49, 145, 36, 101 };
	BTree<int, 3> t;
	for (auto e : a)
	{
		t.Inster(e);
	}
}


int main()
{
	TestBTree();



	return 0;
}