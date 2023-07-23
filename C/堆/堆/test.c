#include"Heap.h"







int main()
{
	int a[] = { 5,2,3,1 };
	Heap hp;
	MoreHeapInit(&hp, a, sizeof(a) / sizeof(HPDataType));
	HeapRise(&hp);
	for (int i = 0; i < hp._size; i++)
	{
		printf("%d\n", hp._a[i]);
	}
	return 0;
}