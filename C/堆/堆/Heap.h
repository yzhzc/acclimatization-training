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



//С�ѳ�ʼ��
void LessHeapInit(Heap* php, HPDataType* a, int n);
//С�ѽ�������
void HeapDown(Heap* php);


//��ѳ�ʼ��
void MoreHeapInit(Heap* php, HPDataType* a, int n);
//�����������
void HeapRise(Heap* php);

//��Ѳ���ڵ�
void MoreHeapPush(Heap* php, HPDataType x);
//С�Ѳ���ڵ�
void LessHeapPush(Heap* php, HPDataType x);


//ɾ���ڵ�
void HeapPop(Heap* php);
//��ȡ�Ѷ�����
HPDataType HeapTop(Heap* php);
//���ٶ�
void HeapDestory(Heap* php);














