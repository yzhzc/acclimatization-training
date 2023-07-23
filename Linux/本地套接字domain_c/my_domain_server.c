#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<sys/un.h>
#include<stddef.h>
#include<stdlib.h>


int main(int argc, char* argv[])
{
    unlink("sock.s");
    //创建unix流式套接字
    int lfd = socket(AF_UNIX, SOCK_STREAM, 0);
    
    //绑定
    struct sockaddr_un myaddr;
    myaddr.sun_family = AF_UNIX;
    strcpy(myaddr.sun_path, "sock.s");
    socklen_t len = offsetof(struct sockaddr_un, sun_path) + strlen(myaddr.sun_path);
    int ret = bind(lfd, (struct sockaddr *)&myaddr, len);
    if(ret < 0)
    {
        perror("bind");
        exit(0);
    }

    //监听
    listen(lfd, 128);

    //提取
    struct sockaddr_un cliaddr;
    socklen_t len_c = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr *)&cliaddr, &len_c);
    printf("新客户端文件目录:%s\n", cliaddr.sun_path);

    //读写
    char buf[1500] = "";
    while(1)
    {
        int n = recv(cfd, buf, sizeof(buf), 0);
        if(n <= 0)
        {
            perror("recv");
            break;
        }
        else
        {
            printf("%s\n", buf);
            send(cfd, buf, n, 0);
        }
    }
    //关闭
    close(lfd);
    close(cfd);

    return 0;
}
