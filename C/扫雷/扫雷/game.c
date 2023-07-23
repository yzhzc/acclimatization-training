#include"game.h"


int leideshuliang(char board[ROWS][COLS], int x, int y)
{
	int shuliang = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (board[x - 1][y - 1] == '#')
			{
				shuliang++;
			}
			y++;
		}
		x++;
		y = y - 3;
	}

	return shuliang;
}


void chushihua(char board[ROWS][COLS], int rows, int cols,char tes)
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= rows; i++)
	{
		for (j = 0; j <= cols; j++)
		{
			board[i][j] = tes;
		}
	}
}


void printqipan(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	printf("----扫 雷 游 戏----\n");
	for (i = 0; i <= row; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d ",i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("----扫 雷 游 戏----\n");
}


void buzhi(char board[ROWS][COLS], int row, int col, int dilei)
{
	int i = 0;
	int x = rand() % row + 1;
	int y = rand() % col + 1;
	for (i = 0; i < dilei; i++)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (board[x][y] != '#')
		{
			board[x][y] = '#';
		}
	}
}


void paicha(char board[ROWS][COLS], char xianshi[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int c = 0;
	while (1)
	{
		printf("请输入坐标：");
		while ((c = getchar()) != '\n' && EOF);
		scanf_s("%d,%d", &x, &y);
		if ((x > 0 && x <= row && y > 0 && col <= col)&&(xianshi[x][y]=='*'))
		{
			if (board[x][y] == '#')
			{
				printf("很遗憾，你被炸死了\n");
				printqipan(board, row, col);
				break;
			}
			else
			{
				int count = leideshuliang(board, x, y);
				xianshi[x][y] =  count+'0';
				printqipan(xianshi, row, col);
			}
		}
		else
		{
			printf("坐标不合法，请重新输入");
		}
	}

}
