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
	//����һ����ά��������������
	char board[ROW][COL] = { 0 };
	//��ʼ����ά������������������滻�ɿո�
	InitBoard(board, ROW, COL);
	//��ӡ����
	DisplayBoard(board, ROW, COL);
	while (1)
	{
		//�������
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//�ж�����Ƿ�Ӯ
		ret = Iswin(board, ROW, COL);
		if (ret != 'r')
		{
			break;
		}

		//��������
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//�жϵ����Ƿ�Ӯ
		if (ret != 'r')
		{
			break;
		}
	}
	if (ret == '*')
	{
		printf("\n���Ӯ\n\n");
	}
	else if (ret == '#')
	{
		printf("\n����Ӯ\n\n");
	}
	else
	{
		printf("\nƽ��\n\n");
	}
}



void test()
{
	int shuru = 0;
	srand((unsigned int)time(0));
	do
	{
		menu();
		printf("�����롷����");
		scanf_s("%d", &shuru);
		switch(shuru)
		{
			case 1:
				printf("��Ϸ��ʼ\n");
				game();
				break;
			case 0:
				printf("�˳���Ϸ\n");
				break;
			default:
				printf("ѡ�����������ѡ��\n");
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







