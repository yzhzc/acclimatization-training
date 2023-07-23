#pragma once

#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>



typedef int HPDataType;

typedef struct Heap
{
	HPDataType* _a;
	int _size;
	int _capacity;
}Heap;



//小堆初始化
void LessHeapInit(Heap* php, HPDataType* a, int n);
//小堆降序排序
void HeapDown(Heap* php);


//大堆初始化
void MoreHeapInit(Heap* php, HPDataType* a, int n);
//大堆升序排序
void HeapRise(Heap* php);

//大堆插入节点
void MoreHeapPush(Heap* php, HPDataType x);
//小堆插入节点
void LessHeapPush(Heap* php, HPDataType x);


//删除节点
void HeapPop(Heap* php);
//获取堆顶数据
HPDataType HeapTop(Heap* php);
//销毁堆
void HeapDestory(Heap* php);














