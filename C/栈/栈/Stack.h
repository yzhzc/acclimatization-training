#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int STDataType;


typedef struct Stack
{
	STDataType* _a;
	int _top;   //ջ���±�
	int _capacity;
}Stack;


//��ʼ��
void StackInit(Stack* pst);
//����ջ
void StackDestroy(Stack* pst);
//��ջ
void StackPush(Stack* pst, STDataType x);
//��ջ
void StackPop(Stack* pst);
//���ݸ���
int StackSize(Stack* pst);
//����1�ǿգ�����0�Ƿǿ�
int StackEmpty(Stack* pst);
//��ȡջ������
STDataType StackTop(Stack* pst);





