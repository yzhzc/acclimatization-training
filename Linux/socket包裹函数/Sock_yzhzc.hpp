#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <unistd.h>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

class Sock
{
private:
    // listen的第二个参数，意义：底层全连接队列的长度 = listen的第二个参数+1
    const static int gbacklog = 128;

public:
    Sock() {}

    //Socket(int IP协议族, int 套接字类型, int 套接字协议)
    static int Socket(int __domain = AF_INET, int __type = SOCK_STREAM, int __protocol = 0)
    {
        int listensock = socket(__domain, __type, __protocol);
        if (listensock < 0)
        {
            exit(2);
        }
        int opt = 1;

        //设置套接字属性setsockopt(套接字, 协议层, 选项, 返回值缓冲区, 缓冲区大小)
        setsockopt(listensock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        return listensock;
    }

    //Bind(int 监听套接字, uint16_t 端口号, string IP地址)
    static void Bind(int sock, uint16_t port, std::string ip = "0.0.0.0")
    {
        struct sockaddr_in local;
        memset(&local, 0, sizeof local);
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &local.sin_addr);
        if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            exit(3);
        }
    }

    //Listen(int 监听套接字)
    static void Listen(int sock)
    {
        if (listen(sock, gbacklog) < 0)
        {
            exit(4);
        }
    }
    // 一般经验
    // const std::string &: 输入型参数
    // std::string *: 输出型参数
    // std::string &: 输入输出型参数.
    //Accept(int 监听套接字, string *接收IP, uint16_t *接收端口号)
    static int Accept(int listensock, std::string *ip, uint16_t *port)
    {
        struct sockaddr_in src;
        socklen_t len = sizeof(src);
        int servicesock = accept(listensock, (struct sockaddr *)&src, &len);
        while (1)
        {
            if (servicesock < 0)
            {
                if ((errno == ECONNABORTED) || (errno == EINTR))//如果是被信号中断和软件层次中断,不能退出
                    continue;
                else
                    return -1;
            }
        }

        if (port)
            *port = ntohs(src.sin_port);
        if (ip)
            *ip = inet_ntoa(src.sin_addr);

        return servicesock;
    }

    //Connect(int 套接字, const string 对方服务器的IP, const uint16_t 对方服务器的端口, int IP协议族)
    static bool Connect(int sock, const std::string &server_ip, const uint16_t &server_port ,int __domain = AF_INET)
    {
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = __domain;
        server.sin_port = htons(server_port);
        server.sin_addr.s_addr = inet_addr(server_ip.c_str());

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0)
            return true;
        else
            return false;
    }

    static int tcp_bind(uint16_t port, std::string ip = "0.0.0.0")
    {
        int listensock = Socket();
        Bind(listensock, port, ip);
        Listen(listensock);

        return listensock;
    }

    ~Sock() {}
};
