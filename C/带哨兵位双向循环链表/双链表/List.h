#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<assert.h>

typedef int LTDateType;

typedef struct listNode
{
	LTDateType data;
	struct listNode* next;
	struct listNode* prev;
}LTNode;



//��ʼ��
LTNode* ListInit();
//ͷ��
void ListPushFront(LTNode* phead, LTDateType x);
//ͷɾ
void ListPopFront(LTNode* phead);
//β��
void ListPushBack(LTNode* phead, LTDateType x);
//βɾ
void ListPopBack(LTNode* phead);
//����
LTNode* ListFind(LTNode* phead, LTDateType x);
//�ڵ�ǰ����
void ListInsert(LTNode* pos, LTDateType x);
//�ڵ�ɾ��
void ListErase(LTNode* pos);
//��ӡ
void ListPrint(LTNode* phead);
//��������
void ListDestroy(LTNode* phead);