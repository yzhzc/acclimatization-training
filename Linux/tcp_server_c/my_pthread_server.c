#include <stdio.h>
#include <pthread.h>
#include "wrap.h"




typedef struct c_info
{
	int cfd;
	struct sockaddr_in cliaddr;
}CINFO;

void* client_fun(void *arg)
{
	CINFO *info = (CINFO *)arg;
	char ip[16] = "";
	printf("新客户端连接 IP = %s port = %d\n",
				inet_ntop(AF_INET, &info->cliaddr.sin_addr.s_addr, ip, 16),
				ntohs(info->cliaddr.sin_port));
	while(1)
	{
		char buf[1024] = "";
		int count = 0;
		count = read(info->cfd, buf, sizeof(buf));
		if(count < 0)
		{
			perror("read!!!");
			break;
		}
		else if(count == 0)
		{
			printf("%s : 客户端关闭\n", ip);
			break;
		}
		else
		{
			printf("%s\n", buf);
			write(info->cfd, buf, count);
		}
	}
	close(info->cfd);
	free(info);
}


int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("argv < 2,传入参数不足");
		return 0;
	}
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	//设置线程属性为创建即分离状态
	int port = atoi(argv[1]);	//将输入的字符串端口号转成整形
	int lfd = tcp4bind(port, NULL);		//绑定端口IP地址
	Listen(lfd, 128);
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	CINFO *info = NULL;
	while(1)
	{
		info = (CINFO*)malloc(sizeof(CINFO));
		int cfd = Accept(lfd, (struct sockaddr *)&cliaddr, &len);
		//char ip[16] = "";
		//printf("新客户端连接 IP = %s port = %d",inet_ntop(AF_TNET, &cliaddr.sin_addr.s_addr, ip, 16),ntohs(cliaddr.sin_port));
		pthread_t pthid;
		info->cfd  = cfd;
		info->cliaddr = cliaddr;
		pthread_create(&pthid, NULL, client_fun, (void *)info);
	}



	return 0;
}
