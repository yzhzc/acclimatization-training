#include<stdio.h>
#include<time.h>
#include<stdlib.h>



#define ROW 10
#define COL 10

void InitBoard(char board[ROW][COL], int row, int col);

void DisplayBoard(char board[ROW][COL], int row, int col);

void PlayerMove(char board[ROW][COL], int row, int col);

void ComputerMove(char board[ROW][COL], int row, int col);

char Iswin(char board[ROW][COL], int row, int col);

int IsFull(char board[ROW][COL], int row, int col);
