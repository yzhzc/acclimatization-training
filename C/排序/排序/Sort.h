#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>


//��������
void InsertSort(int* a, int n);

//ϣ������
void ShellSort(int* a, int n);

//ѡ������
void SelectSort(int* a, int n);

//������
void ADjustDown(int* a, int n, int root);
void HeapRiseSort(int* a, int n);

//ð������
void BubbleSort(int* a, int n);

//�������� �ݹ�ʵ��
//�������� hoare�汾
int PartSort1(int* a, int left, int right);
//�������� �ڿӷ�
int PartSort2(int* a, int left, int right);
//�������� ǰ��ָ�뷨
int PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);

//��������ǵݹ�ʵ��
void QuickSortNonR(int* a, int left, int right);

//�鲢���� �ݹ�ʵ��
void MergerSort(int* a, int n);
//�鲢���� �ǵݹ�ʵ��
void MergeSortNonR(int* a, int n);

//�鲢���� ��ŵ�Ӳ������
void MergeFileSort(int* a, int n);

//��������
void CountSort(int* a, int n);


void PrintArrway(int* a, int n);
