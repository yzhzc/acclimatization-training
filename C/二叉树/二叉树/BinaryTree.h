#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


typedef int BTDataNode;




typedef struct TreeNode
{
	BTDataNode _data;
	struct TreeNode* _left;
	struct TreeNode* _right;
}BTNode;



void PrevOrder(BTNode* root);

//�ڵ���
int TreeSize(BTNode* root);
//��������
BTNode* CreateNode(BTDataNode x);
//���ص�k��ڵ����
int BinaryTreeLeve1KSize(BTNode* root, int k);
//Ѱ��ֵΪk�Ľڵ�
BTNode* TreeFind(BTNode* root, int k);
//�����
void BinaryTreeLeve1order(BTNode* root);
//�ж��Ƿ�Ϊ��ȫ������
int BinaryTreeComplete(BTNode* root);
//���ٶ�����
void DestoryTree(BTNode* root);






typedef BTNode* QDataType;

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

