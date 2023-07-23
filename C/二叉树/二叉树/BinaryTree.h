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

//节点数
int TreeSize(BTNode* root);
//插入数据
BTNode* CreateNode(BTDataNode x);
//返回第k层节点个数
int BinaryTreeLeve1KSize(BTNode* root, int k);
//寻找值为k的节点
BTNode* TreeFind(BTNode* root, int k);
//层遍历
void BinaryTreeLeve1order(BTNode* root);
//判断是否为完全二叉树
int BinaryTreeComplete(BTNode* root);
//销毁二叉树
void DestoryTree(BTNode* root);






typedef BTNode* QDataType;

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

