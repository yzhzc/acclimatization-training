#include"BSTree.h"


int main()
{
	BSTree<int> t;
	int a[] = { 6,3,9,1,7,2,4,8,0,5 };
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.Erase(10);
	t.InOrder();
	
	return 0;
}