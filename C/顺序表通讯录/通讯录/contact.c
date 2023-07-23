#include "contact.h"




//增容
void CheckContact(Contact* pc)
{
	if (pc->sz == pc->capacity)
	{
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (sizeof(PeoInfo) * pc->capacity + INC_SZ));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->capacity = pc->capacity + INC_SZ;
		}
		else
		{
			perror("AddContact");
			printf("增加联系人失败");
			return;
		}
	}
}


//查找
static int FindByName(Contact* pc, char name[])
{
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
		{
			return i;
		}
	}

	return -1;
}


void InitContact(Contact* pc)
{
	pc->data =(PeoInfo*)calloc(sizeof(PeoInfo),DEFAULT_SZ);
	if (pc->data == NULL)
	{
		perror("InitContact");
		return;
	}
	pc->sz = 0;
	pc->capacity = DEFAULT_SZ;

	//读取本地文件保存的数据
	LoadContact(pc);
}

void AddContact(Contact* pc)
{
	//增容
	CheckContact(pc);
	printf("请输入名字：");
	scanf_s("%s", pc->data[pc->sz].name, MAX_NAME);

	printf("请输入年龄：");
	scanf_s("%d", &(pc->data[pc->sz].age));

	printf("请输入性别：");
	scanf_s("%s", pc->data[pc->sz].sex, MAX_SEX);

	printf("请输入电话：");
	scanf_s("%s", pc->data[pc->sz].tele, MAX_tele);

	printf("请输入地址：");
	scanf_s("%s", pc->data[pc->sz].addr, MAX_ADDR);

	pc->sz++;
	printf("\n");
	printf("------------------------------------------\n");
	printf("添加成功\n");
	printf("------------------------------------------\n");

}

void PrintContact(const Contact* pc)
{
	int i = 0;
	printf("\n");
	printf("%-5s\t%-5s\t%-5s\t%-11s\t%-20s\n","名字","年龄","性别","电话","地址");
	for (i = 0; i < pc->sz; i++)
	{
		printf("%-5s\t%-5d\t%-5s\t%-11s\t%-20s\n",
			pc->data[i].name,
			pc->data[i].age, 
			pc->data[i].sex,
			pc->data[i].tele, 
			pc->data[i].addr
		);
	}
}


void DelContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };
	if (pc->sz == 0)
	{
		printf("通讯录为空，无需删除\n");
		return;
	}
	printf("请输入需删除人的姓名：");
	scanf_s("%s", name, MAX_NAME);
	int pos = FindByName(pc, name);//调用联系人查找函数
	if (pos == -1)
	{
		printf("要删除的联系人不存在\n");
		return;
	}
	int i = 0;
	for (i = pos; i < pc->sz-1; i++)
	{
		pc->data[i] = pc->data[i + 1];
	}
	pc->sz--;
	printf("删除成功\n");
}


void SearchContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };
	if (pc->sz == 0)
	{
		printf("通讯录为空，无法查找\n");
		return;
	}
	printf("请输入查找的姓名：");
	scanf_s("%s", name, MAX_NAME);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要查找的联系人不存在\n");
		return;
	}
	printf("\n");
	printf("%-5s\t%-5s\t%-5s\t%-11s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
	printf("%-5s\t%-5d\t%-5s\t%-11s\t%-20s\n",
		pc->data[pos].name,
		pc->data[pos].age,
		pc->data[pos].sex,
		pc->data[pos].tele,
		pc->data[pos].addr
	);
}

void ModifyContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };
	if (pc->sz == 0)
	{
		printf("通讯录为空，无法查找\n");
		return;
	}
	printf("请输入要修改联系人的姓名：");
	scanf_s("%s", name, MAX_NAME);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要修改的联系人不存在\n");
		return;
	}
	else
	{
		printf("请输入 修改后的 名字：");
		scanf_s("%s", pc->data[pos].name, MAX_NAME);

		printf("请输入 修改后的 年龄：");
		scanf_s("%d", &(pc->data[pos].age));

		printf("请输入 修改后的 性别：");
		scanf_s("%s", pc->data[pos].sex, MAX_SEX);

		printf("请输入 修改后的 电话：");
		scanf_s("%s", pc->data[pos].tele, MAX_tele);

		printf("请输入 修改后的 地址：");
		scanf_s("%s", pc->data[pos].addr, MAX_ADDR);
	}
	printf("\n");
	printf("%-5s\t%-5s\t%-5s\t%-11s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
	printf("%-5s\t%-5d\t%-5s\t%-11s\t%-20s\n",
		pc->data[pos].name,
		pc->data[pos].age,
		pc->data[pos].sex,
		pc->data[pos].tele,
		pc->data[pos].addr
	);
}

void DestoryContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
}


void SaveContact(Contact* pc)
{
	FILE* pf = fopen("save.dat", "w");
	if (pf == NULL)
	{
		perror("SaveContact");
		return;
	}
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
	}
	fclose(pf);
	pf = NULL;
}

void LoadContact(Contact* pc)
{
	FILE* pf = fopen("save.dat", "r");
	if (pf == NULL)
	{
		perror("SaveContact");
		return;
	}
	//读文件
	PeoInfo tmp = { 0 };
	while(fread(&tmp, sizeof(PeoInfo), 1, pf))
	{
		CheckContact(pc);
		pc->data[pc->sz] = tmp;
		pc->sz++;
	}
	fclose(pf);
	pf = NULL;
}



