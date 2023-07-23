#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>



#define MAX_NAME 10
#define MAX_SEX 5
#define MAX_tele 15
#define MAX_ADDR 50
#define MAX 1000

#define DEFAULT_SZ 3
#define INC_SZ 2





typedef struct PeoInfo
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_tele];
	char addr[MAX_ADDR];
}PeoInfo;

//ͨѶ¼
typedef struct Contact
{
	PeoInfo* data;//�����ӵ���Ϣ
	int sz;//��¼��Ч��Ϣ�ĸ���
	int capacity;//��¼��ǰͨѶ¼�������
}Contact;

//��ʼ��ͨѶ¼
void InitContact(Contact* pc);
//������ϵ��
void AddContact(Contact* pc);
//��ӡ��ϵ����Ϣ
void PrintContact(const Contact* pc);
//ɾ����ϵ����Ϣ
void DelContact(Contact* pc);
//������ϵ����Ϣ
void SearchContact(Contact* pc);
//�޸�ָ����ϵ����Ϣ
void ModifyContact(Contact* pc);
//����ͨѶ¼
void DestoryContact(Contact* pc);
//����ͨѶ¼���ݵ������ļ�
void SaveContact(Contact* pc);
//���ر�������
void LoadContact(Contact* pc);
//����
void CheckContact��(Contact* pc);


