#include <stdio.h>
#include <sys/epoll.h>
#include "wrap.h"

#define PORT 8888

int main(int argc, char *argv[])
{
	//创建套接字绑定
	int lfd = tcp4bind(PORT, NULL);
	//监听
	Listen(lfd, 128);
	struct sockaddr_in cliaddr;
	socklen_t len = sizeof(cliaddr);
	//创建树
	int epfd = epoll_create(1);
	//sockfd上树
	struct epoll_event ev, evs[1024];
	ev.data.fd = lfd;
	ev.events = EPOLLIN;
	epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
	//循环监听
	while(1)
	{
		int n = epoll_wait(epfd, evs, 1024, -1);
		if(n < 0)
		{
			perror("");
			exit(0);
		}
		else if(n == 0)
		{
			continue;
		}
		else
		{
			//监听到变化
			for(int i = 0; i < n; i++)
			{
				//判断是什么链接,并且是读事件
				if(evs[i].data.fd == lfd && evs[i].events & EPOLLIN)
				{
					//新链接
					char ip[16] = "";
					int cfd = Accept(lfd, (struct sockaddr *) &cliaddr, &len);

					//新sockfd上树
					ev.data.fd = cfd;
					ev.events = EPOLLIN;
					epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);

					printf("新客户端连接:编号 = %d ip = %s port = %d\n",
						   cfd,
						   inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16),
						   ntohs(cliaddr.sin_port));
				}
				else if(evs[i].events & EPOLLIN)
				{
					//新消息
					char buf[1024] = "";
					int count = read(evs[i].data.fd, buf, sizeof(buf));
					if(count < 0)
					{
						perror("read");
						epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &evs[i]);
					}
					else if(count == 0)
					{
						printf("编号 = %d 客户端关闭\n", evs[i].data.fd);
						epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &evs[i]);
						close(evs[i].data.fd);
					}
					else
					{
						printf("编号 = %d 客户端回复:%s\n",evs[i].data.fd, buf);
						char arr[]="服务器回复:";
						Write(evs[i].data.fd, arr, sizeof(arr));
						Write(evs[i].data.fd, buf, count);
					}
				}
			}
		}
	}



	return 0;
}
