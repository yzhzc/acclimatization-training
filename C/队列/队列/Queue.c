#include"Queue.h"



//初始化
void QueueInit(Queue* pq)
{
	assert(pq);
	pq->_head = pq->_tail = NULL;
}


//销毁队列
void QueueDestory(Queue* pq)
{
	assert(pq);
	QueueNode* cur = pq->_head;
	while (cur)
	{
		QueueNode* next = cur->_next;
		free(cur);
		cur = next;
	}
	pq->_head = pq->_tail = NULL;
}


//入尾队
void QueuePush(Queue* pq, QDataType x)
{
	assert(pq);
	QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newnode == NULL)
	{
		perror("QueuePush");
		exit(-1);
	}
	newnode->_data = x;
	newnode->_next = NULL;
	if (pq->_head == NULL)
	{
		pq->_head = pq->_tail = newnode;
	}
	else
	{
		pq->_tail->_next = newnode;
		pq->_tail = newnode;
	}

}


//队头出
void QueuePop(Queue* pq)
{
	assert(pq);
	assert(pq->_head);
	QueueNode* prev = pq->_head->_next;
	free(pq->_head);
	pq->_head = prev;
	if (pq->_head == NULL)
	{
		pq->_tail = NULL;
	}
}


//读取队头的数据
QDataType QueueFront(Queue* pq)
{
	assert(pq);
	assert(pq->_head);

	return pq->_head->_data;
}


//读取队尾的数据
QDataType QueueTail(Queue* pq)
{
	assert(pq);
	assert(pq->_tail);

	return pq->_tail->_data;
}


//返回1是空，返回0是非空
int QueueEmpty(Queue* pq)
{
	assert(pq);
	return pq->_head == NULL ? 1 : 0;
}


//总数据个数
int QueueSize(Queue* pq)
{
	assert(pq);
	QueueNode* cur = pq->_head;
	int size = 0;
	while (cur)
	{
		size++;
		cur = cur->_next;
	}

	return size;
}