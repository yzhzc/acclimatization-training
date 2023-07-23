#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

typedef int QDataType;


//���е�����
typedef struct QueueNode
{
	QDataType _data;
	struct QueueNode* _next;
}QueueNode;

//�������ͷβָ��
typedef struct Queue
{
	QueueNode* _head;
	QueueNode* _tail;
}Queue;


//��ʼ��
void QueueInit(Queue* pq);
//���ٶ���
void QueueDestory(Queue* pq);
//��β��
void QueuePush(Queue* pq, QDataType x);
//��ͷ��
void QueuePop(Queue* pq);
//��ȡ��ͷ������
QDataType QueueFront(Queue* pq);
//��ȡ��β������
QDataType QueueTail(Queue* pq);
//����1�ǿգ�����0�Ƿǿ�
int QueueEmpty(Queue* pq);
//�����ݸ���
int QueueSize(Queue* pq);



