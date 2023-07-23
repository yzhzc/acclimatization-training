#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define PORT 8888

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
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    while (1)
    {
        int n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr, &len);
        if(n < 0)
        {
            perror("recvfrom");
            break;
        }
        else
        {
            printf("%s\n", buf);
            sendto(fd, buf, n, 0, (struct sockaddr *)&cliaddr, len);
        }
    }
    


    //关闭
    close(fd);

    return 0;
}