#include "game.h"


void Start()
{
	printf("***************************************\n");
	printf("****** - 1.PLAY - *** - 0.EIXT - ******\n");
	printf("***************************************\n");
}

void game()
{
	char boom[ROWS][COLS] = { 0 };//����һ������׵�����
	char show[ROWS][COLS] = { 0 };//����һ����ʾ���̱��������
	//��ʼ����������
	chushihua(boom, ROWS, COLS, '0');
	chushihua(show, ROWS, COLS, '*');
	//���õ���
	buzhi(boom, ROW, COL, DILEI);
	//printqipan(boom, ROW, COL);
	printqipan(show, ROW, COL);
	//�Ų����
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
		printf("��������룺");
		scanf_s("%d", &input);

		switch (input)
		{
			case 1:
				printf("��Ϸ��ʼ\n");
				game();
				break;
			case 0:
				printf("��Ϸ����\n");
				break;
			default:
				printf("��������������������\n");
				break;
		}
	} 
	while (input);


	return 0;
}











