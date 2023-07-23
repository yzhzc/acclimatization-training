#include "contact.h"




//����
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
			printf("������ϵ��ʧ��");
			return;
		}
	}
}


//����
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

	//��ȡ�����ļ����������
	LoadContact(pc);
}

void AddContact(Contact* pc)
{
	//����
	CheckContact(pc);
	printf("���������֣�");
	scanf_s("%s", pc->data[pc->sz].name, MAX_NAME);

	printf("���������䣺");
	scanf_s("%d", &(pc->data[pc->sz].age));

	printf("�������Ա�");
	scanf_s("%s", pc->data[pc->sz].sex, MAX_SEX);

	printf("������绰��");
	scanf_s("%s", pc->data[pc->sz].tele, MAX_tele);

	printf("�������ַ��");
	scanf_s("%s", pc->data[pc->sz].addr, MAX_ADDR);

	pc->sz++;
	printf("\n");
	printf("------------------------------------------\n");
	printf("��ӳɹ�\n");
	printf("------------------------------------------\n");

}

void PrintContact(const Contact* pc)
{
	int i = 0;
	printf("\n");
	printf("%-5s\t%-5s\t%-5s\t%-11s\t%-20s\n","����","����","�Ա�","�绰","��ַ");
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
		printf("ͨѶ¼Ϊ�գ�����ɾ��\n");
		return;
	}
	printf("��������ɾ���˵�������");
	scanf_s("%s", name, MAX_NAME);
	int pos = FindByName(pc, name);//������ϵ�˲��Һ���
	if (pos == -1)
	{
		printf("Ҫɾ������ϵ�˲�����\n");
		return;
	}
	int i = 0;
	for (i = pos; i < pc->sz-1; i++)
	{
		pc->data[i] = pc->data[i + 1];
	}
	pc->sz--;
	printf("ɾ���ɹ�\n");
}


void SearchContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };
	if (pc->sz == 0)
	{
		printf("ͨѶ¼Ϊ�գ��޷�����\n");
		return;
	}
	printf("��������ҵ�������");
	scanf_s("%s", name, MAX_NAME);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("Ҫ���ҵ���ϵ�˲�����\n");
		return;
	}
	printf("\n");
	printf("%-5s\t%-5s\t%-5s\t%-11s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
		printf("ͨѶ¼Ϊ�գ��޷�����\n");
		return;
	}
	printf("������Ҫ�޸���ϵ�˵�������");
	scanf_s("%s", name, MAX_NAME);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("Ҫ�޸ĵ���ϵ�˲�����\n");
		return;
	}
	else
	{
		printf("������ �޸ĺ�� ���֣�");
		scanf_s("%s", pc->data[pos].name, MAX_NAME);

		printf("������ �޸ĺ�� ���䣺");
		scanf_s("%d", &(pc->data[pos].age));

		printf("������ �޸ĺ�� �Ա�");
		scanf_s("%s", pc->data[pos].sex, MAX_SEX);

		printf("������ �޸ĺ�� �绰��");
		scanf_s("%s", pc->data[pos].tele, MAX_tele);

		printf("������ �޸ĺ�� ��ַ��");
		scanf_s("%s", pc->data[pos].addr, MAX_ADDR);
	}
	printf("\n");
	printf("%-5s\t%-5s\t%-5s\t%-11s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	//���ļ�
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



