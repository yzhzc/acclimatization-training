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

	//创建通讯录
	Contact con;
	//初始化通讯录
	InitContact(&con);
	do
	{
		//打印菜单
		menu();
		//输入操作码
		printf("请选择：");
		scanf_s("%d", &input);
		switch (input)
		{
		case EXIT:
			//保存信息到本地文件
			//SaveContact(&con);
			//销毁内存中的通讯录数据
			DestoryContact(&con);
			printf("成功退出通讯录\n");
			break;
		case add:
			//增加联系人信息
			AddContact(&con);
			break;
		case del:
			//删除
			DelContact(&con);
			break;
		case search:
			//查找
			SearchContact(&con);
			break;
		case modify:
			//修改指定联系人信息
			ModifyContact(&con);
			break;
		case sort:
			//冒泡排序
			break;
		case print:
			//打印所以联系人信息
			PrintContact(&con);
			break;
		default:
			printf("选择错误，请重新选择\n");
			break;
		}
	} while (input);




	return 0;
}