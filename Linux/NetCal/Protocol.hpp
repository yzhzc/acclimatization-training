#pragma once

#include <iostream>
#include <string>
#include "Sock_yzhzc.hpp"

#define MYSELF
#define SPACE " "
#define SPACE_LEN strlen(SPACE)

class Request
{
public:
    Request()
    {
    }

    Request(int x, int y, char op)
        : x_(x), y_(y), op_(op)
    {
    }

    Request(const Request &copy)
    {
        x_ = copy.x_;
        y_ = copy.y_;
        op_ = copy.op_;
    }

    ~Request()
    {
    }

    //"x_ op_ y_"
    // 序列化
    std::string Serialise()
    {
#ifdef MYSELF
        std::string str;
        str = std::to_string(x_);
        str += SPACE;
        str += op_;
        str += SPACE;
        str += std::to_string(y_);

        return str;
#else
        std::cout << "TODO" << std::endl;
        return nullptr;
#endif
    }

    // 反序列化
    bool Deserialized(const std::string &str)
    {
#ifdef MYSELF
        std::size_t left = str.find(SPACE);
        if (left == std::string::npos)
            return false;

        std::size_t right = str.rfind(SPACE);
        if (right == std::string::npos)
            return false;

        x_ = atoi(str.substr(0, left).c_str());
        y_ = atoi(str.substr(right + SPACE_LEN).c_str());
        if (left + SPACE_LEN > str.size())
            return false;
        op_ = str[left + SPACE_LEN];
        return true;
#else
        std::cout << "TODO" << std::endl;

        return false;
#endif
    }

public:
    int x_;
    int y_;
    char op_; // 计算符号
};

class Response
{
public:
    Response()
    {
    }

    Response(int result, int code)
        : result_(result), code_(code)
    {
    }

    ~Response()
    {
    }

    // "_code result_"
    // 序列化
    std::string Serialise()
    {
#ifdef MYSELF
        std::string s;
        s = std::to_string(code_);
        s += SPACE;
        s += std::to_string(result_);

        return s;
#else
        std::cout << "TODO" << std::endl;
        return nullptr;
#endif
    }

    // 反序列化
    bool Deserialized(const std::string &str)
    {
#ifdef MYSELF
        std::size_t pos = str.find(SPACE);
        if(pos == std::string::npos)
            return false;

        code_ = atoi(str.substr(0, pos).c_str());
        result_ = atoi(str.substr(pos + SPACE_LEN).c_str());
        return true;
#else
        std::cout << "TODO" << std::endl;

        return false;
#endif
    }

public:
    int result_; // 计算结果
    int code_;   // 计算结果的状态码
};

std::string Recv(int sockfd)
{
    char inbuffer[1024];
    ssize_t s = recv(sockfd, inbuffer, sizeof(inbuffer), 0);
    if (s > 0)
        return inbuffer;
    else if(s == 0)
        std::cout << sockfd << "号客户端退出" << std::endl;
    else
        std::cout <<"recv读取失败" << std::endl;

    close(sockfd);
    return "";
}

void Send(int sockfd, const std::string str)
{
    int n = send(sockfd, str.c_str(), str.size(), 0);
    if(n < 0)
        std::cout << sockfd << "send写入失败" << std::endl;

}
