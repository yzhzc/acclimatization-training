#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>


//插入排序
void InsertSort(int* a, int n);

//希尔排序
void ShellSort(int* a, int n);

//选择排序
void SelectSort(int* a, int n);

//堆排序
void ADjustDown(int* a, int n, int root);
void HeapRiseSort(int* a, int n);

//冒泡排序
void BubbleSort(int* a, int n);

//快速排序 递归实现
//快速排序 hoare版本
int PartSort1(int* a, int left, int right);
//快速排序 挖坑法
int PartSort2(int* a, int left, int right);
//快速排序 前后指针法
int PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);

//快速排序非递归实现
void QuickSortNonR(int* a, int left, int right);

//归并排序 递归实现
void MergerSort(int* a, int n);
//归并排序 非递归实现
void MergeSortNonR(int* a, int n);

//归并排序 存放到硬盘排序
void MergeFileSort(int* a, int n);

//计数排序
void CountSort(int* a, int n);


void PrintArrway(int* a, int n);
