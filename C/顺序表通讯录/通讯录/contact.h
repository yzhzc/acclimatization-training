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

//通讯录
typedef struct Contact
{
	PeoInfo* data;//存放添加的信息
	int sz;//记录有效信息的个数
	int capacity;//记录当前通讯录最大容量
}Contact;

//初始化通讯录
void InitContact(Contact* pc);
//增加联系人
void AddContact(Contact* pc);
//打印联系人信息
void PrintContact(const Contact* pc);
//删除联系人信息
void DelContact(Contact* pc);
//查找联系人信息
void SearchContact(Contact* pc);
//修改指定联系人信息
void ModifyContact(Contact* pc);
//销毁通讯录
void DestoryContact(Contact* pc);
//保存通讯录数据到本地文件
void SaveContact(Contact* pc);
//加载本地数据
void LoadContact(Contact* pc);
//增容
void CheckContact（(Contact* pc);


