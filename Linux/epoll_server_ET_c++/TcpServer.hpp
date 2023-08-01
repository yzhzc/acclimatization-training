#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <functional>
#include <unordered_map>
#include "Sock_yzhzc.hpp"
#include "Log.hpp"
#include "Epoll.hpp"
#include "Protocol.hpp"

class TcpServer;
class Connection;

using func_t = std::function<void(Connection *)>;
using callback_t = std::function<void(Connection *, std::string &request)>;

// 常规sock必须要有自己独立的缓冲区
class Connection
{
public:
    Connection(int sock = -1)
        : _sock(-1), _tsvr(nullptr)
    {
    }
    ~Connection()
    {
    }

    // 集合处理程序
    void SetHandler(func_t recv_cb, func_t send_cb, func_t except_cb)
    {
        _recv_cb = recv_cb;
        _send_cb = send_cb;
        _except_cb = except_cb;
    }

public:
    int _sock; // 负责进行IO的文件描述符.

    func_t _recv_cb;        // 读回调
    func_t _send_cb;        // 写回调
    func_t _except_cb;      // 事件回调
    std::string _inbuffer;  // 接收缓冲区
    std::string _outbuffer; // 发送缓冲区
    TcpServer *_tsvr;       // 回值指针

    uint64_t _lasttimestamp; // 规定时间内无消息往来,主动关闭
};

class TcpServer
{
    const static int gport = 8888;
    const static int gnum = 128;

public:
    TcpServer(int port = gport)
        : _port(port), _revs_num(gnum)
    {
        // 1. 建立sock监听
        _ListenSock = Sock::Socket();
        Sock::Bind(_ListenSock, _port);
        Sock::Listen(_ListenSock);
        // 2. 创建多路转接对象
        _poll.CreateEpoll();
        // 3. 将listensock添加到epoll中
        AddConnection(_ListenSock, std::bind(&TcpServer::Accepter, this, std::placeholders::_1), nullptr, nullptr);
        // 4. 构建一个获取就绪事件的缓冲区
        _revs = new struct epoll_event[_revs_num];
    }

    void AddConnection(int sock, func_t recv_cb, func_t send_cb, func_t except_cb)
    {
        // 1. 设置sock非阻塞
        Sock::SetNonBlock(sock);
        // 2. 构建conn对象,封装sock
        Connection *conn = new Connection(sock);
        conn->_sock = sock;
        conn->SetHandler(recv_cb, send_cb, except_cb);
        conn->_tsvr = this;
        conn->_lasttimestamp = time(nullptr);

        // 3. 将sock添加到epoll中
        _poll.AddSockToEpoll(sock, EPOLLIN | EPOLLET); // 任何多路转接服务器,只关心读取事件,写入事件按需进行

        // 4. 将对应Connection*对象指针添加到Connections映射表中
        _connections.insert(std::make_pair(sock, conn));
    }

    // ListenSock专用读回调
    void Accepter(Connection *conn)
    {
        while (true)
        {
            std::string clientip;
            uint16_t clientport;
            int sock = Sock::Accept(conn->_sock, &clientip, &clientport);
            if (sock < 0)
                break;

            // 将sock托管给TcpServer
            AddConnection(sock,
                          std::bind(&TcpServer::Recver, this, std::placeholders::_1),
                          std::bind(&TcpServer::Sender, this, std::placeholders::_1),
                          std::bind(&TcpServer::Excepter, this, std::placeholders::_1));
            logMessage(DEBUG, "accept client %s:%d success, sock: %d",
                       clientip.c_str(), clientport, sock);
        }
    }

    // 修改epoll节点监听事件(读/写)
    void EnableReadWrite(Connection *conn, bool readable, bool writeable)
    {
        uint32_t events = ((readable ? EPOLLIN : 0) | (writeable ? EPOLLOUT : 0));
        bool res = _poll.CtrlEpoll(conn->_sock, events);
        assert(res);
    }

    // 读回调
    void Recver(Connection *conn)
    {
        // logMessage(DEBUG, "Recver event exists");
        conn->_lasttimestamp = time(nullptr);
        const int num = 1024;
        bool err = false;
        while (true)
        {
            char buffer[num];
            ssize_t n = recv(conn->_sock, buffer, sizeof(buffer) - 1, 0);
            if (n < 0)
            {
                if (errno == ECONNABORTED || errno == EINTR) // 如果是被信号中断和软件层次中断,不能退出
                    continue;
                else if (errno == EAGAIN || errno == EWOULDBLOCK) // 平繁空读,或读取缓冲区满了
                    break;
                else
                {
                    logMessage(ERROR, "recv error, %d: %s", errno, strerror(errno));
                    conn->_except_cb(conn);
                    err = true;
                    break;
                }
            }
            else if (n == 0)
            {
                logMessage(ERROR, "client[%d] quit, server close[%d]", conn->_sock, conn->_sock);
                conn->_except_cb(conn);
                break;
            }
            else
            {
                // 将一次读取的数据存储到各自独立的缓冲区
                buffer[n] = 0;
                conn->_inbuffer += buffer;
            }
        }
        if (!err)
        {
            // 执行上层业务
            std::vector<std::string> messages;
            SpliteMassage(conn->_inbuffer, &messages);
            for (auto &msg : messages)
                _cb(conn, msg);
        }
    }

    // 写回调
    void Sender(Connection *conn)
    {
        while (true)
        {
            ssize_t n = send(conn->_sock, conn->_outbuffer.c_str(), conn->_outbuffer.size(), 0);
            if (n < 0)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK) // 平繁空写或者发送缓冲区满了
                    break;
                else if (errno == ECONNABORTED || errno == EINTR) // 被软件层面中断返回信号打断
                    continue;
                else
                {
                    logMessage(ERROR, "send error, %d: %s", errno, strerror(errno));
                    conn->_except_cb(conn);
                    break;
                }
            }
            else
            {
                conn->_outbuffer.erase(0, n);
                if (conn->_outbuffer.empty())
                    break;
            }
        }
        // 没发完不能关闭写监听
        if (conn->_outbuffer.empty())
            EnableReadWrite(conn, true, false);
        else
            EnableReadWrite(conn, true, true);
    }

    // 异常回调
    void Excepter(Connection *conn)
    {
        if (!IsConnectionExists(conn->_sock))
            return;

        // 1. 从epoll中移除
        if (!_poll.DelFromEpoll(conn->_sock))
            assert(1);
        // 2. 从map表中移除
        _connections.erase(conn->_sock);
        // 3. close(sock)
        close(conn->_sock);
        // 4. delete 对应的conn
        delete conn;
    }

    // 执行一次epoll_wait
    void LoopOnce()
    {
        int n = _poll.WaitEpoll(_revs, _revs_num);
        for (int i = 0; i < n; i++)
        {
            int sock = _revs[i].data.fd;
            uint32_t revents = _revs[i].events;

            // 文件描述符出错或者被挂断,依旧执行读写事件,在读写回调里触发异常回调
            if (revents & EPOLLERR || revents & EPOLLHUP)
                revents |= (EPOLLIN | EPOLLOUT);
            // 确认是读事件
            if (revents & EPOLLIN)
            {
                if (IsConnectionExists(sock) && _connections[sock]->_recv_cb != nullptr)
                    _connections[sock]->_recv_cb(_connections[sock]);
            }
            if (revents & EPOLLOUT)
            {
                if (IsConnectionExists(sock) && _connections[sock]->_send_cb != nullptr)
                    _connections[sock]->_send_cb(_connections[sock]);
            }
        }
    }

    void ConnectAliveCheck()
    {
        //遍历所有的_connections, 检查conn最近活动时间,关闭超时连接
        for(auto &iter : _connections)
        {
            uint64_t currtime = time(nullptr);
            uint64_t deadtime = currtime - iter.second->_lasttimestamp;
            //if(deadtime > xxxxxxx)
        }
    }

    // 根据就绪的事件,进行特定事件派发
    void Dispather(callback_t cb)
    {
        _cb = cb;
        while (true)
        {
            LoopOnce();
            ConnectAliveCheck();
        }
    }

    // 判断文件描述符是否在map表中
    bool IsConnectionExists(int sock)
    {
        auto iter = _connections.find(sock);
        if (iter == _connections.end())
            return false;

        return true;
    }

    ~TcpServer()
    {
        if (_ListenSock >= 0)
            close(_ListenSock);

        if (_revs)
            delete[] _revs;
    }

private:
    int _ListenSock;
    int _port;
    Epoll _poll;
    std::unordered_map<int, Connection *> _connections;
    struct epoll_event *_revs; // 接收epoll返回的变化节点的数组
    int _revs_num;             // 接收数组的大小
    callback_t _cb;            // 上层业务处理回调
};
