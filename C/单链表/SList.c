#include"SList.h"

//876

//�����½ڵ�������
SLTNode* BuySListNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}


//��ӡ����
void SListPrint(SLTNode* phead)
{
	while (phead != NULL)
	{
		printf("%d->", phead->data);
		phead = phead->next;
	}
	printf("NULL\n");
}


//β��
void SListPushBack(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySListNode(x);
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		SLTNode* tail = *pphead;
		//��ָ��ָ���������ڵ�
		while (tail->next)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}

//ͷ��
void SListPushFront(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySListNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}

//ͷɾ
void SListPopFront(SLTNode** pphead)
{
	if (*pphead == NULL)
	{
		return;
	}
	else
	{
		SLTNode* next = (*pphead)->next;
		free(*pphead);
		*pphead = next;
	}
}

//βɾ
void SListPopBack(SLTNode** pphead)
{
	SLTNode* tail = *pphead;
	SLTNode* prev = NULL; 
	//��ָ��ָ���������ڵ�
	while (tail->next)
	{
		prev = tail;
		tail = tail->next;
	}
	free(tail);
	tail = NULL;
	prev->next = NULL;
}

//����
SLTNode* SListFind(SLTNode* phead, SLTDataType x)
{
	SLTNode* tail = phead;
	while (tail)
	{
		if (tail->data == x)
		{
			return tail;
		}
		else
		{
			tail = tail->next;
		}
	}
	return NULL; 
}


//��posλ��ǰ����һ���ڵ�
void SListInsert(SLTNode** pphead, SLTDataType x, SLTNode* pos)
{
	SLTNode* newnode = BuySListNode(x);
	SLTNode* posPrev = *pphead;
	while (posPrev->next!=pos)
	{
		posPrev = posPrev->next;
		assert(posPrev != NULL);
	}
	posPrev->next = newnode;
	newnode->next = pos;
}


//����pos��һ���ڵ�
void SListErase(SLTNode** pphead, SLTNode* pos)
{
	SLTNode* tail = *pphead;
	SLTNode* posPrev = NULL;
	while (tail)
	{
		if (tail == pos)
		{
			posPrev->next = tail->next;
			free(tail);
			tail = NULL;
			return;
		}
		else
		{
			posPrev = tail;
			tail = tail->next;
		}
	}
	assert(tail != NULL);
}


//��������
void SListDestory(SLTNode** pphead)
{
	SLTNode* prev = NULL;
	while ((*pphead)->next)
	{
		prev = (*pphead)->next;
		free(*pphead);
		*pphead = prev;
	}
	free(*pphead);
	*pphead = NULL;
}



























































































