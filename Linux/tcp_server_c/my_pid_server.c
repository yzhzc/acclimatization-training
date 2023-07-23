#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include "wrap.h"





void free_process(int sig)
{
	pid_t pid;
	while(1)
	{
		pid = waitpid(-1, NULL, WNOHANG);
		if(pid <= 0)//小于零子进程全部退出,等于0目前没有进程退出
		{
			break;
		}
		else
		{
			printf("回收进程号: %d\n", pid);
			//fflush(0);
		}
	}
}

int main(int argc, char *argv[])
{
	//设置阻塞集,阻塞子进程退出信号,防止在主进程还未注册信号回调的情况下退出
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGCHLD);
	sigprocmask(SIG_BLOCK, &set, NULL);
	int flag = 1;	//判断是否注册信号回调函数
	//1.设置服务器IP,端口等参数
	int lfd = tcp4bind(8001, NULL);
	//2.监听
	Listen(lfd, 128);
	//3.提取,收到信息后回射
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	while(1)
	{
		char ip[16] = "";
		int cfd = Accept(lfd,(struct sockaddr *)&cliaddr, &len);
		printf("新客户端连接: ip = %s port = %d\n",
				inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16),
				ntohs(cliaddr.sin_port)); 
		//创建子进程
		pid_t pid;
		pid = fork();
		if(pid < 0)
		{
			perror("fork!!!!!!");
			exit(0);
		}
		else if(pid == 0)	//子进程
		{
			//关闭监听lfd
			close(lfd);
			while(1)
			{
				char buf[1024] = "";
				int n = read(cfd, buf, sizeof(buf));
				if(n == 0)
				{
					printf("无内容读取,客户端关闭\n");
					close(cfd);
					exit(0);
				}
				else if(n < 0)
				{
					perror("read!!!!!");
					close(cfd);
					exit(0);
				}
				else
				{
					printf("收到客户端消息:%s\n", buf);
					write(cfd, buf, n);	//原封不动返回给客户端
					
				}
			}
		}
		else	//父进程
		{
			close(cfd);
			if(flag)
			{
				//回收子进程
				//注册信号回调
				struct sigaction act;
				act.sa_flags = 0;
				act.sa_handler = free_process;	
				sigaction(SIGCHLD, &act, NULL);
				sigprocmask(SIG_UNBLOCK, &set, NULL);//信号回调建立完,解除阻塞信号集
				flag = 0;
			}

			//回收子进程
			//注册信号回调
		}
	}
	//关闭	
	return 0;
}
