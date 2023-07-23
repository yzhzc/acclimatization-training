#pragma once

#include "Sock_yzhzc.hpp"
#include "Log.hpp"
#include <functional>
#include <pthread.h>
#include <vector>


using func_t = std::function<void(int)>;

class TcpServer;


class ThreadData
{
public:
    ThreadData(int sock, TcpServer* server)
        :sock_(sock)
        ,server_(server)
    {}
    ~ThreadData()
    {}
public:
    int sock_;
    TcpServer* server_;
};


class TcpServer
{
private:
    static void* ThreadRoutine(void* args)
    {
        pthread_detach(pthread_self());
        ThreadData* td = static_cast<ThreadData*>(args);
        td->server_->Excute(td->sock_);
        delete td;
        return nullptr;
    }

public:
    TcpServer(const uint16_t& port, const std::string& ip = "0.0.0.0")
    {
        int listensockfd = sock_.Socket();
        sock_.Bind(listensockfd, port, ip);
        sock_.Listen(listensockfd);
        listensockfd_ = listensockfd;
    }

    //绑定回调函数
    void BindHander(func_t func)
    {
        funcs_.push_back(func);
    }

    //执行回调函数
    void Excute(int sockfd)
    {
        for(auto& f : funcs_)
        {
            f(sockfd);
        }
    }

    void Start()
    {
        while(1)
        {
            std::string client_ip;
            uint16_t client_port;
            int sockfd = sock_.Accept(listensockfd_, &client_ip, &client_port);
            if(sockfd < 0)
                continue;  

            logMessage(NORMAL, "新链接: sockfd = %d", sockfd);
            pthread_t tid;
            ThreadData* td = new ThreadData(sockfd, this);
            pthread_create(&tid, nullptr, ThreadRoutine, (void*)td);
        }

    }

    ~TcpServer()
    {
        if(listensockfd_ >= 0)
            close(listensockfd_);
    }
private:
    int listensockfd_;
    Sock sock_;
    std::vector<func_t> funcs_;
};