#include "game.h"



void menu()
{
	printf("******************************************\n");
	printf("****** -- 1.play-- **** -- 0.exit-- ******\n");
	printf("******************************************\n");
}

void game()
{
	char ret = 'a';
	//创建一个二维数组存放棋盘数据
	char board[ROW][COL] = { 0 };
	//初始化二维数组里面的所有数据替换成空格
	InitBoard(board, ROW, COL);
	//打印棋盘
	DisplayBoard(board, ROW, COL);
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断玩家是否赢
		ret = Iswin(board, ROW, COL);
		if (ret != 'r')
		{
			break;
		}

		//电脑下棋
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断电脑是否赢
		if (ret != 'r')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("\n玩家赢\n\n");
	}
	else if (ret == '#')
	{
		printf("\n电脑赢\n\n");
	}
	else
	{
		printf("\n平局\n\n");
	}
}



void test()
{
	int shuru = 0;
	srand((unsigned int)time(0));
	do
	{
		menu();
		printf("请输入》》：");
		scanf_s("%d", &shuru);
		switch(shuru)
		{
			case 1:
				printf("游戏开始\n");
				game();
				break;
			case 0:
				printf("退出游戏\n");
				break;
			default:
				printf("选择错误，请重新选择\n");
				break;
		}

	} 
	while(shuru);
}


int main()
{
	test();


	return 0;
}







