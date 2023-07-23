#include"List.h"



//�����¿ռ�
LTNode* BuyListNode(LTDateType x)
{
	LTNode* newnode = (LTNode*)malloc(sizeof(LTNode));
	newnode->data = x;
	newnode->next = NULL;
	newnode->prev = NULL;

	return newnode;
}



//��ʼ��
LTNode* ListInit()
{
	LTNode* phead = (LTNode*)malloc(sizeof(LTNode));
	phead->next = phead;
	phead->prev = phead;

	return phead;
}


//ͷ��
void ListPushFront(LTNode* phead, LTDateType x)
{
	assert(phead);
	//LTNode* newnode = BuyListNode(x);
	//newnode->next = phead->next;
	//newnode->prev = phead;
	//phead->next = newnode;
	ListInsert(phead->next, x);
}


//ͷɾ
void ListPopFront(LTNode* phead)
{
	assert(phead);
	assert(phead->next != phead);
	LTNode* tail = phead->next;
	phead->next = tail->next;
	tail->next->prev = phead;
	free(tail);
	tail = NULL;
}


//β��
void ListPushBack(LTNode* phead, LTDateType x)
{
	assert(phead);
	//LTNode* tail = phead->prev;
	//LTNode* newnode = BuyListNode(x);
	//tail->next = newnode;
	//newnode->prev = tail;
	//newnode->next = phead;
	//phead->prev = newnode;
	ListInsert(phead, x);
}


//βɾ
void ListPopBack(LTNode* phead)
{
	assert(phead);
	assert(phead->prev != phead);
	LTNode* tail = phead->prev;
	phead->prev = tail->prev;
	tail->prev->next = phead;
	free(tail);
	tail = NULL;
}


//����
LTNode* ListFind(LTNode* phead, LTDateType x)
{
	assert(phead);
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}

	return NULL;
}


//�ڵ�ǰ����
void ListInsert(LTNode* pos, LTDateType x)
{
	assert(pos);
	LTNode* newnode = BuyListNode(x);
	newnode->next = pos;
	newnode->prev = pos->prev;
	pos->prev = newnode;
	newnode->prev->next = newnode;
}


//�ڵ�ɾ��
void ListErase(LTNode* pos)
{
	assert(pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
	pos = NULL;
}


//��ӡ
void ListPrint(LTNode* phead)
{
	assert(phead);
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}


//��������
void ListDestroy(LTNode* phead)
{
	LTNode* cur = phead->next;
	while (cur != phead)
	{
		LTNode* next = cur->next;
		free(cur);
		cur = next;
	}
}