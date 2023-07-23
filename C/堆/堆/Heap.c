#include"Heap.h"


//交换
void Swap(HPDataType* p1, HPDataType* p2)
{
	HPDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

//将单位堆内大数上升
void MoreAdjustUp(HPDataType* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//将单位堆内小数上升
void LessAdjustUp(HPDataType* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//将单位堆内小数下沉
void MoreAdjustDown(HPDataType* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] > a[child])
		{
			child++;
		}
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//将单位堆内大数下沉
void LessAdjustDown(HPDataType* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n - 1)
	{
		if (child + 1 < n - 1 && a[child + 1] < a[child])
		{
			child++;
		}
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//小堆初始化
void LessHeapInit(Heap* php, HPDataType* a, int n)
{
	php->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	if (php->_a != NULL)
	{
		memcpy(php->_a, a, sizeof(HPDataType) * n);
		php->_size = n;
		php->_capacity = n;
	}
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		LessAdjustDown(php->_a, n, i);
	}
}

//大堆初始化
void MoreHeapInit(Heap* php, HPDataType* a, int n)
{
	php->_a = (HPDataType*)malloc(sizeof(HPDataType) * n);
	if (php->_a != NULL)
	{
		memcpy(php->_a, a, sizeof(HPDataType) * n);
		php->_size = n;
		php->_capacity = n;
	}
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		MoreAdjustDown(php->_a, n, i);
	}
}

//大堆升序排序
void HeapRise(Heap* php)
{
	int end = php->_size - 1;
	while (end > 0)
	{
		Swap(&php->_a[0], &php->_a[end]);
		MoreAdjustDown(php->_a, end, 0);
		end--;
	}
}

//小堆降序排序
void HeapDown(Heap* php)
{
	int end = php->_size-1;
	while (end > 0)
	{
		Swap(&php->_a[0], &php->_a[end]);
		LessAdjustDown(php->_a, end, 0);
		end--;
	}
}

//销毁堆
void HeapDestory(Heap* php);

//大堆插入节点
void MoreHeapPush(Heap* php, HPDataType x)
{
	assert(php);
	if (php->_size == php->_capacity)
	{
		php->_capacity *= 2;
		HPDataType* tmp = (HPDataType*)realloc(php->_a, sizeof(HPDataType) * php->_capacity);
		if (tmp != NULL)
		{
			php->_a = tmp;
		}
	}
	php->_a[php->_size] = x;
	MoreAdjustUp(php->_a, php->_size);
	php->_size++;
}

//小堆插入节点
void LessHeapPush(Heap* php, HPDataType x)
{
	assert(php);
	if (php->_size == php->_capacity)
	{
		php->_capacity *= 2;
		HPDataType* tmp = (HPDataType*)realloc(php->_a, sizeof(HPDataType)*php->_capacity);
		if (tmp != NULL)
		{
			php->_a = tmp;
		}
	}
	php->_a[php->_size] = x;
	LessAdjustUp(php->_a, php->_size);
	php->_size++;
}

//删除节点
void HeapPop(Heap* php)
{
	assert(php);
	assert(php->_size > 0);
	Swap(&php->_a[0], &php->_a[php->_size - 1]);
	php->_size--;
	LessAdjustDown(php->_a, php->_size, 0);
}

//获取堆顶数据
HPDataType HeapTop(Heap* php)
{
	assert(php);

	return php->_a[0];
}