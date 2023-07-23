#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef int STDataType;


typedef struct Stack
{
	STDataType* _a;
	int _top;   //栈顶下标
	int _capacity;
}Stack;


//初始化
void StackInit(Stack* pst);
//销毁栈
void StackDestroy(Stack* pst);
//入栈
void StackPush(Stack* pst, STDataType x);
//出栈
void StackPop(Stack* pst);
//数据个数
int StackSize(Stack* pst);
//返回1是空，返回0是非空
int StackEmpty(Stack* pst);
//获取栈顶数据
STDataType StackTop(Stack* pst);





