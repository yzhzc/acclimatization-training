#include <stdio.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include "wrap.h"

#define PORT 8888


int main(int argc, char* argv[])
{
	//创建套接字绑定
	int lfd = tcp4bind(PORT, NULL);
	//监听
	Listen(lfd, 128);
	//初始化FD_SET集合
	int maxfd = lfd;
	fd_set oldset, newset;
	FD_ZERO(&newset);
	FD_ZERO(&oldset);
	FD_SET(lfd, &oldset);
	while(1)
	{
		newset = oldset;
		int n = select(maxfd + 1, &newset, NULL, NULL, NULL);
		if(n < 0)	//监听失败
		{
			perror("select");
			break;
		}
		else if(n == 0)    //监听单位无变化
		{
			continue;
		}
		else	//监听到文件描述符变化
		{
			//检测是否有新的链接到来
			if(FD_ISSET(lfd, &newset))
			{
				//提取新的链接
				struct sockaddr_in cliaddr;
				socklen_t len = sizeof(cliaddr);
				char ip[16] = "";
				int cfd = Accept(lfd, (struct sockaddr *) &cliaddr, &len);
				printf("新客户端连接:编号 = %d ip = %s port = %d\n",
						cfd,
						inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16),
						ntohs(cliaddr.sin_port));

				//将新链接添加到oldset集合
				FD_SET(cfd, &oldset);
				//更新检测文件描述符范围
				if(cfd > maxfd)
					maxfd = cfd;

				if(n == 1)
					continue;
			}

			//遍历传出的newset集合,处理变化数据
			for(int i = lfd + 1; i <= maxfd; i++)
			{
				if(FD_ISSET(i, &newset))
				{
					char buf[1500] = "";
					int ret = Read(i, buf, sizeof(buf));
					if(ret < 0)
					{
						//将出错的文件描述符关闭,从oldset中剔除;
						perror("read");
						close(i);
						FD_CLR(i, &oldset);
					}
					else if(ret == 0)
					{
						printf("编号 = %d 客户端关闭\n", i);
						close(i);
						FD_CLR(i, &oldset);
					}
					else
					{
						printf("编号 = %d 客户端回复:%s\n",i, buf);
						char arr[]="服务器回复:";
						Write(i, arr, sizeof(arr));
						Write(i, buf, ret);
					}
				}
			}
		}
	}

	return 0;
}
