#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdlib.h>
#include<assert.h>

typedef int SLTDataType;


typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;

//��ӡ����
void SListPrint(SLTNode* phead);
//β��
void SListPushBack(SLTNode** pphead, SLTDataType x);
//ͷ��
void SListPushFront(SLTNode** pphead, SLTDataType x);
//ͷɾ
void SListPopFront(SLTNode** pphead);
//βɾ
void SListPopBack(SLTNode** pphead);
//����
SLTNode* SListFind(SLTNode* phead, SLTDataType x);
//��posλ��ǰ����һ���ڵ�
void SListInsert(SLTNode** pphead, SLTDataType x, SLTNode* pos);
//����pos��һ���ڵ�
void SListErase(SLTNode** pphead, SLTNode* pos);
//��������
void SListDestory(SLTNode** pphead);



