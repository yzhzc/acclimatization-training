#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <cstdio>
#include <pthread.h>

typedef void* (*fun_t)(void*);

class ThreadData
{
public:
    void* _args;    //回调函数参数
    std::string _name;  //线程名
};

class Thread
{
    //using fun_t = std::function<void* (void *)>;
public:
    Thread(int num, fun_t callback, void* args)
        :_func(callback)
    {
        char nameBuffer[64];
        snprintf(nameBuffer, sizeof(nameBuffer), "Thread-%d", num);
        _name = nameBuffer;
        tdata._args = args;
        tdata._name = _name;
    }

    std::string name()
    {
        return _name;
    }
    
    void join()
    {
        pthread_join(_tid, nullptr);
    }

    void start()
    {
        pthread_create(&_tid, nullptr, _func, (void*)&tdata);
    }

    ~Thread()
    {

    }
private:
    std::string _name;  //线程名
    pthread_t _tid; //线程号
    fun_t _func;    //线程执行的回调函数
    ThreadData tdata;   //回调函数参数
};
