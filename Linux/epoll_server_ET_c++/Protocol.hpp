#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

// 100+19X100+19X
#define SEP "X"
#define SEP_LEN strlen(SEP)
#define SPACE " "
#define SPACE_LEN strlen(SPACE)

// 将传入的缓冲区切分
void SpliteMassage(std::string &buffer, std::vector<std::string> *out)
{
    while (true)
    {
        size_t pos = buffer.find(SEP);
        if (std::string::npos == pos)
            break;

        std::string message = buffer.substr(0, pos); // 截取子串
        buffer.erase(0, pos + SEP_LEN);              // 去除截取的子串
        out->push_back(message);
    }
}

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
        std::string str;
        str = std::to_string(x_);
        str += SPACE;
        str += op_;
        str += SPACE;
        str += std::to_string(y_);

        return str;
    }

    // 反序列化
    bool Deserialized(const std::string &str)
    {
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
        std::string s;
        s = std::to_string(code_);
        s += SPACE;
        s += std::to_string(result_);

        return s;
    }

    // 反序列化
    bool Deserialized(const std::string &str)
    {
        std::size_t pos = str.find(SPACE);
        if (pos == std::string::npos)
            return false;

        code_ = atoi(str.substr(0, pos).c_str());
        result_ = atoi(str.substr(pos + SPACE_LEN).c_str());
        return true;
    }

public:
    int result_; // 计算结果
    int code_;   // 计算结果的状态码
};

// 添加报头报尾length\r\ncode\r\n
std::string Encode(std::string &s)
{
    std::string new_package = std::to_string(s.size());
    new_package += SEP;
    new_package += s;
    new_package += SEP;
    std::cout << "Encode:" << new_package << std::endl;

    return new_package;
}
