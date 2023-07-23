#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>


#define PORT 8887

int main(int argc,char* argv[])
{
    //创建套接字
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    //绑定
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(PORT);
    char ip[] = "127.0.0.1";
    inet_pton(AF_INET, ip, &myaddr.sin_addr.s_addr);
    int ret = bind(fd,(struct sockaddr *)&myaddr, sizeof(myaddr));
    if(ret < 0)
    {
        perror("bind");
        exit(0);
    }

    //读写
    char buf[1500] = ""; 

    //接受数据结构体
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);

    //发送数据结构体
    struct sockaddr_in dstaddr;
    dstaddr.sin_family = AF_INET;
    dstaddr.sin_port = htons(atoi(argv[2]));
    dstaddr.sin_addr.s_addr = inet_addr(argv[1]);
    int n = 0;
    while (1)
    {
        n = read(STDIN_FILENO, buf, sizeof(buf));
        sendto(fd, buf, n, 0, (struct sockaddr *)&dstaddr, sizeof(dstaddr));
        memset(buf, 0, sizeof(buf));
        n = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        if(n < 0)
        {
            perror("recvfrom");
            break;
        }
        else
        {
            printf("%s\n", buf);
        }
    }
    


    //关闭
    close(fd);

    return 0;
}