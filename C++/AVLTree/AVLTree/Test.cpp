#include"AVLTree.h"



int main()
{
	int a[] = { 16,3,17,11,9,26,18,14,15 };
	//int a[] = { 4,2,6,1,3,5,15,7,16,14 };
	AVLTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}

	t.Erase(17);
	t.Erase(15);
	cout << t.Erase(20) << endl;
	//t.Erase(5);
	//t.Erase(6);
	t.InOrder();
	cout << t.IsBalance();


	return 0;
}
