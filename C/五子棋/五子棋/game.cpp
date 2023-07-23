#include "game.h"




void InitBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}


void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		int j = 0;
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j], board[i][j], board[i][j]);
			if (j < col - 1)
			{
				printf("|");
			}
		}
		printf("\n");
		if (i < row - 1)
		{
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
				{
					printf("|");
				}
			}
		}
		printf("\n");
	}
}


void PlayerMove(char board[ROW][COL], int row, int col)
{
    int x = 0;
	int y = 0;
	int c = 0;
	while (1)
	{
		printf("玩家行动：\n");
		printf("请输入棋子坐标(X,Y)：");

		while ((c = getchar()) != '\n' && EOF)
		{
			;//上一次输入溢出的数据会残留在输入缓冲区，将其清除。
		}

		scanf_s("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*';
				break;
			}
			else
			{
				printf("\n该坐标被占用,请重新输入\n\n");
			}
		}
		else
		{
			printf("坐标超出界限，请重新输入\n");
		}
	}

}


void ComputerMove(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("电脑行动：\n");
    x = rand() % row;
	y = rand() % col;
	printf("电脑输入的坐标：%d,%d\n", x+1, y+1);
	
	while (1)
	{
		if (x >= 0 && x <= row-1 && y >= 0 && y <= col-1)
		{
			if (board[x][y] == ' ')
			{
				board[x][y] = '#';
				break;
			}
		}
	
	}
}


int IsFull(char board[ROW][COL], int row, int col)//判断是否平局，返回1是平局，返回0游戏继续。
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
			}
		}
	}
    return 1;
} 


char Iswin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < 3; i++)//横
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
			return (board[i][1]);
		}
	}
	for (i = 0; i < 3; i++)//竖
	{
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[1][i] != ' ')
		{
			return (board[1][i]);
		}
	}
	//右斜
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{
		return(board[1][1]);
	}
	//左斜
	if (board[0][2] == board[1][1] && board[1][1]==board[2][0] && board[0][2] != ' ')
	{
		return(board[1][1]);
	}
	//平局
	if (1 == IsFull(board, ROW, COL))
	{
		return ('q');
	}
	return 'r';
}