#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

typedef int QDataType;


//队列单链表
typedef struct QueueNode
{
	QDataType _data;
	struct QueueNode* _next;
}QueueNode;

//存放链表头尾指针
typedef struct Queue
{
	QueueNode* _head;
	QueueNode* _tail;
}Queue;


//初始化
void QueueInit(Queue* pq);
//销毁队列
void QueueDestory(Queue* pq);
//入尾队
void QueuePush(Queue* pq, QDataType x);
//队头出
void QueuePop(Queue* pq);
//读取队头的数据
QDataType QueueFront(Queue* pq);
//读取队尾的数据
QDataType QueueTail(Queue* pq);
//返回1是空，返回0是非空
int QueueEmpty(Queue* pq);
//总数据个数
int QueueSize(Queue* pq);



