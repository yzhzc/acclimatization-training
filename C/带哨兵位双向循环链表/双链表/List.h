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



//初始化
LTNode* ListInit();
//头插
void ListPushFront(LTNode* phead, LTDateType x);
//头删
void ListPopFront(LTNode* phead);
//尾插
void ListPushBack(LTNode* phead, LTDateType x);
//尾删
void ListPopBack(LTNode* phead);
//查找
LTNode* ListFind(LTNode* phead, LTDateType x);
//节点前插入
void ListInsert(LTNode* pos, LTDateType x);
//节点删除
void ListErase(LTNode* pos);
//打印
void ListPrint(LTNode* phead);
//销毁链表
void ListDestroy(LTNode* phead);