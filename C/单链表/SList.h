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

//打印链表
void SListPrint(SLTNode* phead);
//尾插
void SListPushBack(SLTNode** pphead, SLTDataType x);
//头插
void SListPushFront(SLTNode** pphead, SLTDataType x);
//头删
void SListPopFront(SLTNode** pphead);
//尾删
void SListPopBack(SLTNode** pphead);
//查找
SLTNode* SListFind(SLTNode* phead, SLTDataType x);
//在pos位置前插入一个节点
void SListInsert(SLTNode** pphead, SLTDataType x, SLTNode* pos);
//擦除pos这一个节点
void SListErase(SLTNode** pphead, SLTNode* pos);
//销毁链表
void SListDestory(SLTNode** pphead);



