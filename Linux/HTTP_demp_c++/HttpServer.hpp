#pragma once

#include <iostream>
#include <string>
#include <functional>
#include "Sock_yzhzc.hpp"

class HttpServer
{
public:
    using func_t = std::function<void(int)>;

public:
    HttpServer(const uint16_t &port, func_t func)
        : port_(port), func_(func)
    {
        listenSock_ = sock_.Socket();
        sock_.Bind(listenSock_, port_);
        sock_.Listen(listenSock_);
    }

    ~HttpServer()
    {
    }

    void Start()
    {
        signal(SIGCHLD, SIG_IGN);
        while (true)
        {
            std::string clientTp;
            uint16_t client_port = 0;
            int sockfd = sock_.Accept(listenSock_, &clientTp, &client_port);
            if (sockfd < 0)
                continue;

            if (fork() == 0)
            {
                close(listenSock_);
                func_(sockfd);
                exit(0);
            }
            close(sockfd);
        }
    }

private:
    int listenSock_;
    uint16_t port_;
    Sock sock_;
    func_t func_;
};