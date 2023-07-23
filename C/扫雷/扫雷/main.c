#include "game.h"


void Start()
{
	printf("***************************************\n");
	printf("****** - 1.PLAY - *** - 0.EIXT - ******\n");
	printf("***************************************\n");
}

void game()
{
	char boom[ROWS][COLS] = { 0 };//创建一个存放雷的数组
	char show[ROWS][COLS] = { 0 };//创建一个显示棋盘表面的数组
	//初始化两个棋盘
	chushihua(boom, ROWS, COLS, '0');
	chushihua(show, ROWS, COLS, '*');
	//布置地雷
	buzhi(boom, ROW, COL, DILEI);
	//printqipan(boom, ROW, COL);
	printqipan(show, ROW, COL);
	//排查地雷
	paicha(boom, show, ROW, COL);

}



int main()
{
	int input = 0;
	int c = 0;

	srand((unsigned int)time(0));

	Start();

	do
	{
		printf("请玩家输入：");
		scanf_s("%d", &input);

		switch (input)
		{
			case 1:
				printf("游戏开始\n");
				game();
				break;
			case 0:
				printf("游戏结束\n");
				break;
			default:
				printf("输入错误，请玩家重新输入\n");
				break;
		}
	} 
	while (input);


	return 0;
}











