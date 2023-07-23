#include"SList.h"

//876

//开辟新节点存放数据
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


//打印链表
void SListPrint(SLTNode* phead)
{
	while (phead != NULL)
	{
		printf("%d->", phead->data);
		phead = phead->next;
	}
	printf("NULL\n");
}


//尾插
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
		//让指针指向链表最后节点
		while (tail->next)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}

//头插
void SListPushFront(SLTNode** pphead, SLTDataType x)
{
	SLTNode* newnode = BuySListNode(x);
	newnode->next = *pphead;
	*pphead = newnode;
}

//头删
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

//尾删
void SListPopBack(SLTNode** pphead)
{
	SLTNode* tail = *pphead;
	SLTNode* prev = NULL; 
	//让指针指向链表最后节点
	while (tail->next)
	{
		prev = tail;
		tail = tail->next;
	}
	free(tail);
	tail = NULL;
	prev->next = NULL;
}

//查找
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


//在pos位置前插入一个节点
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


//擦除pos这一个节点
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


//销毁链表
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



























































































