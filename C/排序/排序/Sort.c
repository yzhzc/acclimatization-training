#include"Sort.h"
#include"Stack.h"

//����
void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}


void PrintArrway(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}


//��������
void InsertSort(int* a, int n)
{
	assert(a);
	for (int i = 0; i < n - 1; i++)
	{
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			//�ж�end��һ�����С��end��end��һ����end���ǣ�ָ�����
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				break;
			}
			a[end + 1] = tmp;
		}
	}
	PrintArrway(a, n);
}

//ϣ������
void ShellSort(int* a, int n)
{
	assert(a);
	int gap = n;
	while (gap != 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				//�ж�end���3�����С��end��end���3����end���ǣ�ָ�����
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
				a[end + gap] = tmp;
			}
		}
	}
	PrintArrway(a, n);
}

//ѡ������
void SelectSort(int* a, int n)
{
	assert(a);

	int begin = 0;
	int end = n - 1;
	while (begin < end)
	{
		int maxi = begin;
		int mini = begin;
		for (int i = begin + 1; i <= end; i++)
		{
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
			if (a[i] < a[mini])
			{
				mini = i;
			}
		}
		Swap(&a[begin], &a[mini]);
		if (begin == maxi)
		{
			maxi = mini;
		}
		Swap(&a[end], &a[maxi]);
		begin++;
		end--;
	}
	PrintArrway(a, n);
}

//������

//�Ѷ����µ���
void ADjustDown(int* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child] < a[child + 1])
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

//���������
void HeapRiseSort(int* a, int n)
{
	for (int i = (n - 2) / 2; i >= 0; i--)
	{
		ADjustDown(a, n, i);
	}
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[0], &a[end]);
		ADjustDown(a, end, 0);
		end--;
	}
	PrintArrway(a, n);
}

//ð������
void BubbleSort(int* a, int n)
{
	int end = n;
	while (end >= 0)
	{
		int exchange = 0;
		for (int i = 1; i < end; i++)
		{
			if (a[i-1] > a[i])
			{
				Swap(&a[i-1], &a[i]);
				exchange = 1;
			}
		}
		if (exchange == 0)
		{
			break;
		}
		end--;
	}
	PrintArrway(a, n);
}

//�������� �ݹ�ʵ��
//�������� hoare�汾


//ȡǰ�к�������ȡ��С���м�������±�
int GetMidIndex(int* a, int begin, int end)
{
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid])
	{
		if (a[mid] < a[end])
		{
			return mid;
		}
		else if (a[begin] > a[end])
		{
			return begin;
		}
		else
		{
			return end;
		}
	}
	else
	{
		if (a[mid] > a[end])
		{
			return mid;
		}
		else if (a[begin] < a[end])
		{
			return begin;
		}
		else
		{
			return end;
		}
	}
}
//����ָ�뷨
int PartSort1(int* a, int begin, int end)
{
	//����ȡ����ĩβ������
	int midIndex = GetMidIndex(a, begin, end);
	Swap(&a[end], &a[midIndex]);

	//ȡĩβ������Ϊ�Ƚϵ�key
	int ketindex = end;

	while (begin < end)
	{
		while (begin < end && a[begin] <= a[ketindex])
		{
			++begin;
		}
		while (begin < end && a[end] >= a[ketindex])
		{
			--end;
		}
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin], &a[ketindex]);

	return begin;
}

//�������� �ڿӷ�
int PartSort2(int* a, int begin, int end)
{
	assert(a);
	//����ȡ����ĩβ������
	int midIndex = GetMidIndex(a, begin, end);
	Swap(&a[end], &a[midIndex]);
	//�Ƚ�β����ȡ��������ĩβ�ǿյĿ�λ
	int key = a[end];
	while (begin < end)
	{
		//�ҵ�ǰ����key�����
		while (begin < end && a[begin] <= key)
		{
			begin++;
		}
		//���ҵ���������У�
		a[end] = a[begin];
		while (begin < end && a[end] >= key)
		{
			end--;
		}
		a[begin] = a[end];
	}
	//ǰָ��������ָ�룬��Ϊ��ָ������λ���ǿӣ�ֱ�ӽ�key���룻
	a[begin] = key;
}

//�������� ǰ��ָ�뷨
int PartSort3(int* a, int begin, int end)
{
	assert(a);
	int key = a[end];
	int cur = begin;
	int prev = begin - 1;
	while (cur <= end)
	{
		if (a[cur] <= key && ++prev != cur)
		{
			Swap(&a[prev], &a[cur]);
		}
		cur++;
	}

	return prev;
}
void QuickSort(int* a, int left, int right)
{
	assert(a);
	if (left >= right)
		return;

	//����10���������ݹ�
	if ((right - left + 1) > 10)
	{
		//��������ĩβ����������ŵ����������ȷ��λ�ã�
		int div = PartSort3(a, left, right);
		//�ֳ� [left , div - 1] �� [div + 1 , right]

		PrintArrway(a, 10);
		printf("\n");
		printf("[%d,%d]%d[%d,%d]\n", a[left], a[div - 1], div, a[div + 1], a[right]);

		QuickSort(a, left, div - 1);
		QuickSort(a, div + 1, right);
	}
	//С��ʮ�����жϣ���ʱ�Ѿ���������ò�������
	else
	{
		//�������ַ����left��λ�ã�
		InsertSort(a + left, right - left + 1);
	}
}

//��������ǵݹ�ʵ��
void QuickSortNonR(int* a, int left, int right)
{
	//����һ��ջ
	Stack st;
	StackInit(&st);
	StackPush(&st, right);
	StackPush(&st, left);

	while (!StackEmpty(&st))
	{
		int begin = StackTop(&st);
		StackPop(&st);
		int end = StackTop(&st);
		StackPop(&st);

		int div = PartSort3(a, begin, end);

		if (div + 1 < end)
		{
			StackPush(&st, end);
			StackPush(&st, div + 1);
		}
		if (div - 1 > begin)
		{
			StackPush(&st, div - 1);
			StackPush(&st, begin);
		}
	}
	StackDestroy(&st);
	//PrintArrway(a, right + 1);
}

//�鲢����

//�鲢��tmp
void MergeArr(int* a, int begin1, int end1, int begin2, int end2, int* tmp)
{
	int cut = 0;
	int left = begin1;
	//���������������໥�Ƚϣ�С�ķ���tmp��ֱ������һ�������
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (a[begin1] <= a[begin2])
			tmp[cut++] = a[begin1++];
		else
			tmp[cut++] = a[begin2++];
	}
	//��ʣ����Ǹ�������������ν��Ŵ���tmp
	while (begin1 <= end1)
		tmp[cut++] = a[begin1++];
	while (begin2 <= end2)
		tmp[cut++] = a[begin2++];
	//���鲢�õ�tmp������ԭʼ�����Ӧλ��
	memcpy(a + left, tmp, sizeof(int) * cut);
}

void _MergerSort(int* a, int left, int right, int* tmp)
{
	if (left >= right)
		return;

	int mid = (right + left) / 2;
	_MergerSort(a, left, mid, tmp);
	_MergerSort(a, mid+1, right, tmp);
	MergeArr(a, left, mid, mid + 1, right, tmp);
}

//�ݹ�ʵ��
void MergerSort(int* a, int n)
{
	assert(a);
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergerSort(a, 0, n - 1, tmp);


	free(tmp);
	tmp = NULL;
	PrintArrway(a, n);

}

//�鲢���� �ǵݹ�ʵ��
void MergeSortNonR(int* a, int n)
{
	assert(a);
	int* tmp = (int*)malloc(sizeof(int) * n);
	int gap = 1;
	while (gap <= n)
	{
		for (int i = 0; i < n; i += 2 * gap)
		{
			int begin1 = i;
			int end1 = i + gap - 1;
			int begin2 = i + gap;
			int end2 = i + 2 * gap - 1;
			if (begin2 >= n)
				break;
			if (end2 >= n)
				end2 = n - 1;
			MergeArr(a, begin1, end1, begin2, end2, tmp);
		}
		gap *= 2;
	}
	PrintArrway(a, n);
}


//�ļ���������

//��ȡ�����ļ����鲢��mfile
void _MergeFile(const char* file1, const char* file2, const char* mfile)
{
	FILE* data1 = fopen(file1, "r");
	if (data1 == NULL)
	{
		printf("���ļ�ʧ��");
		exit(-1);
	}
	FILE* data2 = fopen(file2, "r");
	if (data2 == NULL)
	{
		printf("���ļ�ʧ��");
		exit(-1);
	}
	FILE* fin = fopen(mfile, "w");
	if (fin == NULL)
	{
		printf("���ļ�ʧ��");
		exit(-1);
	}

	int num1, num2;
	int ret1 = fscanf(data1, "%d\n", &num1);
	int ret2 = fscanf(data2, "%d\n", &num2);
	while (ret1 != EOF && ret2 != EOF)
	{
		if (num1 < num2)
		{
			fprintf(fin, "%d\n", num1);
			ret1 = fscanf(data1, "%d\n", &num1);
		}
		else
		{
			fprintf(fin, "%d\n", num2);
			ret2 = fscanf(data2, "%d\n", &num2);
		}
	}

	while (ret1 != EOF)
	{
		fprintf(fin, "%d\n", num1);
		ret1 = fscanf(data1, "%d\n", &num1);
	}
	while (ret2 != EOF)
	{
		fprintf(fin, "%d\n", num2);
		ret2 = fscanf(data2, "%d\n", &num2);
	}

	fclose(data1);
	fclose(data2);
	fclose(fin);
}

//�ļ�����
void MergeFileSort(int* a, int n)
{
	assert(a);
	int cut = 0;
	int size = 10;
	int tmp[10];
	int i = 0;
	char subfile[15];
	int filei = 0;
	while (cut < n)
	{
		if (i < size)
		{
			tmp[i++] = a[cut++];
		}
		else
		{
			QuickSort(tmp, 0, size - 1);
			sprintf(subfile, "sub\\sub_sort%d", filei++);
			FILE* fin = fopen(subfile, "w");
			for (int i = 0; i < size; i++)
			{
				fprintf(fin, "%d\n", tmp[i]);
			}
			fclose(fin);
			i = 0;
		}
	}
	if (i > 0)
	{
		QuickSort(tmp, 0, i-1);
		sprintf(subfile, "sub\\sub_sort%d", filei++);
		FILE* fin = fopen(subfile, "w");
		for (int j = 0; j < i; j++)
		{
			fprintf(fin, "%d\n", tmp[j]);
		}
		fclose(fin);
	}

	char mfile[100];
	char file1[100] = {"sub\\sub_sort0"};
	char file2[100];

	cut = n / size;
	if (n % size != 0)
		cut++;

	for (i = 1; i < cut; i++)
	{
		//����һ���ļ�����file2
		sprintf(file2, "sub\\sub_sort%d", i);
		sprintf(mfile, "sub\\0 %d", i);

		_MergeFile(file1, file2, mfile);
		strcpy(file1, mfile);
	}
}


//��������
void CountSort(int* a, int n)
{
	assert(a);

	int min = a[0];
	int max = a[0];
	for (int i = 1; i < n; ++i)
	{
		if (a[i] > max)
			max = a[i];

		if (a[i] < min)
			min = a[i];
	}

	int range = max - min - 1;
	int* countArr = (int*)malloc(sizeof(int) * range);
	memset(countArr, 0, sizeof(int) * range);

	//ͳ�ƴ���
	for (int i = 0; i < n; i++)
	{
		countArr[a[i] - min]++;
	}

	//����
	int index = 0;
	for (int j = 0; j < range; j++)
	{
		while (countArr[j]--)
		{
			a[index++] = j + min;
		}
	}

	PrintArrway(a, n);
}















