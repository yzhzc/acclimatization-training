#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<time.h>
#define SIZE 64


int main(void)
{
	pid_t pid = -1;
	//1.创建子进程，父进程退出
	pid = fork();
	if(-1 == pid)
	{
		perror("fork");
		return 1;
	}
	if(pid > 0)
	{ 
		//父进程退出，形式上退出终端控制
		exit(0);
	}

	//2.创建新的会话，完全脱离终端控制
	pid = setsid();
	if(-1 == pid)
	{
                perror("setsid");
                return 1;
        }

	//3.改变当前工作目录
	int ret = -1;
	ret = chdir("/");
	if(-1 == ret)
	{
                perror("chdir");
                return 1;
        }

	//4.设置权限掩码
	umask(0);

	//5.关闭文件描述符
	close(STDIN_FILENO);
        close(STDOUT_FILENO);
	close(STDERR_FILENO);

	//6.执行核心任务
	//每隔一秒输出当前时间名文件到~/test/mydaemon/中
	char file_name[SIZE];
	struct tm *pT = NULL;
	while(1)
	{
		//获取当前时间，以秒为单位，从1970-01-01 00:00:00 开始到现在的秒数
		time_t t = -1;
		t = time(NULL);
		pT = localtime(&t);
		if(NULL == pT)
		{
			perror("localtime");
			return 1;
		}	
		memset(file_name, 0, SIZE);
		
		sprintf(file_name, "%s%d%d%d%d%d%d.log", "touch ~/test/mydaemon/",
			pT->tm_year + 1900,
			pT->tm_mon + 1,
			pT->tm_mday,
			pT->tm_hour,
			pT->tm_min,
			pT->tm_sec);

		system(file_name);
		sleep(2);
	}
	
	return 0;
}

