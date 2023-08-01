#pragma once

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include "Sock_yzhzc.hpp"

//#define MYSELF 0
#define SPACE " "
#define SPACE_LEN strlen(SPACE)
#define SEP "/r/n"
#define SEP_LEN strlen(SEP)

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
        Json::Value root;
        root["x"] = x_;
        root["y"] = y_;
        root["op"] = op_;
        Json::FastWriter writer;
        
        return writer.write(root);
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
        Json::Value root;
        Json::Reader reader;
        reader.parse(str, root);
        x_ = root["x"].asInt();
        y_ = root["y"].asInt();
        op_ = root["op"].asInt();

        return true;
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
    {}

    Response(int result, int code)
        : result_(result), code_(code)
    {}

    ~Response()
    {}

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
        Json::Value root;
        root["code"] = code_;
        root["result"] = result_;
        Json::FastWriter writer;
        
        return writer.write(root);
#endif
    }

    // 反序列化
    bool Deserialized(const std::string &str)
    {
#ifdef MYSELF
        std::size_t pos = str.find(SPACE);
        if (pos == std::string::npos)
            return false;

        code_ = atoi(str.substr(0, pos).c_str());
        result_ = atoi(str.substr(pos + SPACE_LEN).c_str());
        return true;
#else
        Json::Value root;
        Json::Reader reader;
        reader.parse(str, root);

        result_ = root["result"].asInt();
        code_ = root["code"].asInt();

        return true;
#endif
    }

public:
    int result_; // 计算结果
    int code_;   // 计算结果的状态码
};

bool Recv(int sockfd, std::string &out)
{
    char buffer[1024];
    ssize_t s = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (s > 0)
    {
        buffer[s] = 0;
        out += buffer;
        return true;
    }
    else if (s == 0)
    {
        std::cout << sockfd << "号客户端退出" << std::endl;
    }
    else
    {
        std::cout << "recv读取失败" << std::endl;
    }

    close(sockfd);
    return false;
}

void Send(int sockfd, const std::string str)
{
    int n = send(sockfd, str.c_str(), str.size(), 0);
    if (n < 0)
        std::cout << sockfd << "send写入失败" << std::endl;
}

// 判断接收的报文是否完整
std::string Decode(std::string &buffer)
{
    // 1. 找到报头分割位置
    std::size_t pos = buffer.find(SEP);
    if (pos == std::string::npos)
        return "";

    //2. 获取内容长度
    int size = atoi(buffer.substr(0, pos).c_str());
    
    //3. 计算实际内容长度
    int content_size = buffer.size() - pos - 2 * SEP_LEN;//std::cout << "content_size: " << content_size << std::endl;
    if (content_size == size)
    {
        buffer.erase(0, pos + SEP_LEN);
        std::string s = buffer.substr(0, size);
        buffer.erase(0, size + SEP_LEN);
        

        return s;
    }

    return "";
}

//添加报头报尾length\r\ncode\r\n
std::string Encode(std::string &s)
{
    std::string new_package = std::to_string(s.size());
    new_package += SEP;
    new_package += s;
    new_package += SEP;
                            std::cout << "Encode:" << new_package << std::endl;


    return new_package;
}
