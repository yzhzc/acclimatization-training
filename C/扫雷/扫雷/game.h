#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define	ROW 9
#define	COL 9
#define	ROWS ROW+2
#define	COLS COL+2
#define	DILEI 10


//��ʼ������
void chushihua(char board[ROWS][COLS], int rows, int cols, char tes);

//��ӡ��������Ļ��
void printqipan(char board[ROWS][COLS], int row, int col);

//���õ���
void buzhi(char board[ROWS][COLS], int row, int col, int dilei);

//�Ų����
void paicha(char board[ROWS][COLS], char xianshi[ROWS][COLS], int row, int col);

//�׵�����
int leideshuliang(char board[ROWS][COLS], int x, int y);







