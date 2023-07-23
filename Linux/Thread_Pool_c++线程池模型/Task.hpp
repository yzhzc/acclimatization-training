#pragma once

#include <iostream>
#include <functional>

typedef std::function<int(int, int)> func_t;

class Task
{

public:
    Task(){}
    Task(int x, int y, func_t func)
        :x_(x), y_(y), func_(func)
    {}
    void operator ()(const std::string& name)
    {
        std::cout << "线程" << name << "处理完成, 结果是: " 
            << x_ << "+" << y_ << "=" << func_(x_, y_) << std::endl;
    }
public:
    int x_;
    int y_;
    // int type;
    func_t func_;
};