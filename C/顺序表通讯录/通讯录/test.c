#include "contact.h"





void menu()
{
	printf("\n");
	printf("||||||||||||||||||||||||||||||||||||||||||\n");
	printf("====   1 . add     ####   2 . del     ====\n");
	printf("====   3 . search  ####   4 . modify  ====\n");
	printf("====   5 . sort    ####   6 . print   ====\n");
	printf("====              0.exit              ====\n");
	printf("||||||||||||||||||||||||||||||||||||||||||\n");
	printf("\n");

}


enum Option
{
	EXIT,
	add,
	del,
	search,
	modify,
	sort,
	print
};


int main()
{
	int input = 0;

	//����ͨѶ¼
	Contact con;
	//��ʼ��ͨѶ¼
	InitContact(&con);
	do
	{
		//��ӡ�˵�
		menu();
		//���������
		printf("��ѡ��");
		scanf_s("%d", &input);
		switch (input)
		{
		case EXIT:
			//������Ϣ�������ļ�
			//SaveContact(&con);
			//�����ڴ��е�ͨѶ¼����
			DestoryContact(&con);
			printf("�ɹ��˳�ͨѶ¼\n");
			break;
		case add:
			//������ϵ����Ϣ
			AddContact(&con);
			break;
		case del:
			//ɾ��
			DelContact(&con);
			break;
		case search:
			//����
			SearchContact(&con);
			break;
		case modify:
			//�޸�ָ����ϵ����Ϣ
			ModifyContact(&con);
			break;
		case sort:
			//ð������
			break;
		case print:
			//��ӡ������ϵ����Ϣ
			PrintContact(&con);
			break;
		default:
			printf("ѡ�����������ѡ��\n");
			break;
		}
	} while (input);




	return 0;
}