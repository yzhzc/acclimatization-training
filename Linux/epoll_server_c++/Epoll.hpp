#pragma once

#include <iostream>
#include <sys/epoll.h>

class Epoll
{
public:
    static const int gsize = 256;

public:
    //创建根节点
    static int CreateEpoll()
    {
        int epfd = epoll_create(gsize);
        if(epfd > 0)
            return epfd;

        exit(5);
    }

    //CtlEpoll(int 根节点, int 这个节点进行的动作, int 对应文件描述符, uint32_t 监听的事件)
    static bool CtlEpoll(int epfd, int oper, int sockfd, uint32_t events)
    {
        struct epoll_event ev;
        ev.data.fd = sockfd;
        ev.events = events;
        int n = epoll_ctl(epfd, oper, sockfd, &ev);

        return n == 0;
    }

    //WaitEpoll(int 根节点, struct epoll_event *接收变化节点队列, int 接收队列大小, int等待时间)
    static int WaitEpoll(int epfd, struct epoll_event *revs, int num, int timeout)
    {
        return epoll_wait(epfd, revs, num, timeout);
    }
};