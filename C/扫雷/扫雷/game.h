#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define	ROW 9
#define	COL 9
#define	ROWS ROW+2
#define	COLS COL+2
#define	DILEI 10


//初始化棋盘
void chushihua(char board[ROWS][COLS], int rows, int cols, char tes);

//打印棋盘在屏幕上
void printqipan(char board[ROWS][COLS], int row, int col);

//布置地雷
void buzhi(char board[ROWS][COLS], int row, int col, int dilei);

//排查地雷
void paicha(char board[ROWS][COLS], char xianshi[ROWS][COLS], int row, int col);

//雷的数量
int leideshuliang(char board[ROWS][COLS], int x, int y);







