#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <cassert>
#include <unistd.h>
#include <memory>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>
#include "Log.hpp"

class Sock
{
private:
    // listen的第二个参数，意义：底层全连接队列的长度 = listen的第二个参数+1
    const static int gbacklog = 128;

public:
    Sock() {}

    // Socket(int IP协议族, int 套接字类型, int 套接字协议)
    static int Socket(int __domain = AF_INET, int __type = SOCK_STREAM, int __protocol = 0)
    {
        int listensock = socket(__domain, __type, __protocol);
        if (listensock < 0)
        {
            logMessage(FATAL, "create socket error, %d:%s", errno, strerror(errno));
            exit(2);
        }
        int opt = 1;

        // 设置套接字属性setsockopt(套接字, 协议层, 选项, 返回值缓冲区, 缓冲区大小)
        setsockopt(listensock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        logMessage(NORMAL, "创建socket成功, listensock: %d", listensock);

        return listensock;
    }

    // Bind(int 监听套接字, uint16_t 端口号, string IP地址)
    static void Bind(int sock, uint16_t port, std::string ip = "0.0.0.0")
    {
        struct sockaddr_in local;
        memset(&local, 0, sizeof local);
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &local.sin_addr);
        if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
        {
            logMessage(FATAL, "bind error, %d:%s", errno, strerror(errno));
            exit(3);
        }
    }

    // Listen(int 监听套接字)
    static void Listen(int sock)
    {
        if (listen(sock, gbacklog) < 0)
        {
            logMessage(FATAL, "listen error, %d:%s", errno, strerror(errno));
            exit(4);
        }
        logMessage(NORMAL, "监听中");
    }
    // 一般经验
    // const std::string &: 输入型参数
    // std::string *: 输出型参数
    // std::string &: 输入输出型参数.
    // Accept(int 监听套接字, string *接收IP, uint16_t *接收端口号)
    static int Accept(int listensock, std::string* ip, uint16_t* port)
    {
        struct sockaddr_in src;
        socklen_t len = sizeof(src);
        int servicesock;
        while (1)
        {
            servicesock = accept(listensock, (struct sockaddr*)&src, &len);
            if (servicesock < 0)
            {
                if ((errno == ECONNABORTED) || (errno == EINTR))//如果是被信号中断和软件层次中断,不能退出
                {
                    continue;
                }  
                else
                {
                    logMessage(ERROR, "accept error, %d:%s", errno, strerror(errno));
                    return -1;
                }
                    
            }
            break;
        }

        if (port)
            *port = ntohs(src.sin_port);
        if (ip)
            *ip = inet_ntoa(src.sin_addr);

        return servicesock;
    }

    // Connect(int 套接字, const string 对方服务器的IP, const uint16_t 对方服务器的端口, int IP协议族)
    static bool Connect(int sock, const std::string &server_ip, const uint16_t &server_port, int __domain = AF_INET)
    {
        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = __domain;
        server.sin_port = htons(server_port);
        server.sin_addr.s_addr = inet_addr(server_ip.c_str());

        int ret = connect(sock, (struct sockaddr *)&server, sizeof(server));

        if (ret < 0)
        {
            logMessage(ERROR, "连接服务器失败, %d:%s", errno, strerror(errno));
            return false;
        }

        logMessage(NORMAL, "连接服务器成功");
        return true;
    }

    static int tcp_bind(uint16_t port, std::string ip = "0.0.0.0")
    {
        int listensock = Socket();
        Bind(listensock, port, ip);
        Listen(listensock);

        return listensock;
    }

    bool Recv(int sockfd, std::string &buf) const
    {
        buf.clear();
        char tmp[1024 * 10] = {0};
        // [注意!] 这里的读并不算很严谨, 因为一次 recv 并不能保证把所有的数据都全部读完
        // 参考 man 手册 MSG_WAITALL 节.
        ssize_t read_size = recv(sockfd, tmp, sizeof(tmp), 0);
        if (read_size < 0)
        {
            perror("recv");
            return false;
        }
        if (read_size == 0)
        {
            return false;
        }
        
        //如果已经全部读取,拷贝到上层缓冲区
        buf.assign(tmp, read_size);
        return true;
    }

    bool Send(int sockfd, const std::string &buf) const
    {
        ssize_t write_size = send(sockfd, buf.data(), buf.size(), 0);
        if (write_size < 0)
        {
            perror("send");
            return false;
        }
        return true;
    }

    ~Sock() {}
};
