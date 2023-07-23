#ifndef __EPOLL_SERVER_HPP__
#define __EPOLL_SERVER_HPP__

#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include "Log.hpp"
#include "Sock_yzhzc.hpp"
#include "Epoll.hpp"

static const int default_port = 8888;
static const int gnum = 64;


class EpolServer
{
    using func_t = std::function<void(std::string)>;

public:
    EpolServer(func_t HandlerRequest, const int &port = default_port)
        :_port(port)
        ,_revs_num(gnum)
        ,_HandlerRequest(HandlerRequest)
    {
        //1.申请epoll返回空间
        _revs = new struct epoll_event[_revs_num];

        //2.创建listensock监听
        _liststensock = Sock::Socket();
        Sock::Bind(_liststensock, _port);
        Sock::Listen(_liststensock);

        //3.创建epoll模型
        _epfd = Epoll::CreateEpoll();
        logMessage(DEBUG, "init success, listensock: %d, epfd: %d", _liststensock, _epfd);

        //4._liststensock上树
	    if(Epoll::CtlEpoll(_epfd, EPOLL_CTL_ADD, _liststensock, EPOLLIN))
            logMessage(DEBUG, "ADD listensock to epoll success.");
        else
            exit(6);
    }

    //读取监听到的数据
    void Recver(int sockfd)
    {
        //1.读取数据
        char buffer[10240];
        ssize_t n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if(n > 0)
        {
            buffer[n] = 0;
            _HandlerRequest(buffer);
        }
        else if(n == 0)
        {
            //对方关闭
            bool res = Epoll::CtlEpoll(_epfd, EPOLL_CTL_DEL, sockfd, 0);
            assert(res);
            (void)res;
            close(sockfd);
            logMessage(NORMAL, "cilent %d quit, me too....", sockfd);
        }
        else
        {
            bool res = Epoll::CtlEpoll(_epfd, EPOLL_CTL_DEL, sockfd, 0);
            assert(res);
            (void)res;
            close(sockfd);
            logMessage(NORMAL, "cilent recv %d error, close error sock", sockfd);
        }
        //2.处理数据
    }

    //提取新socket上树监听
    void Accepter(int liststensock)
    {
        std::string clientIP;
        uint16_t clientport;
        int sockfd = Sock::Accept(liststensock, &clientIP, &clientport);
        if(sockfd < 0)
        {
            logMessage(WARNING, "Accept error!");
            return;
        }
        if(Epoll::CtlEpoll(_epfd, EPOLL_CTL_ADD, sockfd, EPOLLIN))
        {
            logMessage(DEBUG, "ADD new sockfd : %d to epoll success", sockfd);
        }
        else
        {
            logMessage(WARNING, "CtlEpoll ADD sockfd error!");
            return;
        }
    }

    //处理返回的变化节点
    void HandlerEvents(int n)
    {
        if(n < 0)
            exit(7);

        for(int i = 0; i < n; i++)
        {
            uint32_t revents = _revs[i].events;
            int sockfd = _revs[i].data.fd;
            if(revents & EPOLLIN)
            {
                if (sockfd == _liststensock)
                    Accepter(_liststensock);
                else
                    Recver(sockfd);
            }
        }
    }

    //loopOnce(int 等待时间)
    void LoopOnce(int timeout)
    {
        int n = Epoll::WaitEpoll(_epfd, _revs, _revs_num, timeout);
        if (n == 0)
        {
            logMessage(DEBUG, "timeout......");
        }
        else if (n < 0)
        {
            logMessage(WARNING, "epoll wait error:", strerror(errno));
        }
        else
        {
            // 等待成功
            logMessage(WARNING, "get a event");
            HandlerEvents(n);
        }
    }

    void start()
    {
        int timeout = 1000;
        while(1)
        {
            LoopOnce(timeout);
        }
    }

    ~EpolServer()
    {
        if (_liststensock >= 0)
            close(_liststensock);

        if (_epfd >= 0)
            close(_epfd);

        if (_revs)
            delete[] _revs;
    }

private:
    int _liststensock;  //监听sock
    int _epfd;  //根节点
    uint16_t _port; //服务器端口
    struct epoll_event *_revs;  //epoll返回队列
    int _revs_num;  //epoll返回队列大小
    func_t _HandlerRequest; //存放回调函数
};

#endif