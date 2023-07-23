#pragma once
#include <vector>
#include <queue>
#include <unistd.h>
#include <cstdio>
#include "thread.hpp"
#include "lockGuard.hpp"
#include "Task.hpp"
#include "Log.hpp"


const int g_thread_num = 3;

template<class T>
class ThreadPool
{
//静态函数获取类内参数的函数
public:
    //获取锁
    pthread_mutex_t *getMutex()
    {
        return &lock;
    }

    //队列判空
    bool isEmpty()
    {
        return _task_queue.empty();
    }

    //等待条件变量
    void waitCond()
    {
        pthread_cond_wait(&cond, &lock);
    }

    //从队列中获取一个任务
    T getTask()
    {
        T t = _task_queue.front();
        _task_queue.pop();

        return t;
    }

public:
    ThreadPool(int thread_num = g_thread_num)
        :_num(thread_num)
    {
        for(int i = 1; i <= _num; i++)
        {
            _threads.push_back(new Thread(i, routine, this));
        }
        pthread_mutex_init(&lock, nullptr);
        pthread_cond_init(&cond, nullptr);
    }

    //启动按钮
    void run()
    {
        for(auto& iter : _threads)
        {
            iter->start();
            logMessage(NORMAL, "%s%s", iter->name().c_str(), "启动成功");
        }
    }

    static void* routine(void* args)    //类内静态函数无this指针,无法访问类内成员
    {
        ThreadData* td = (ThreadData*) args;
        ThreadPool<T>* tp = (ThreadPool<T>*)td->_args;
        while(1)
        {
            T task;
            {
                lockGuard lockguard(tp->getMutex());
                while(tp->isEmpty())
                {
                    tp->waitCond();
                }
                task = tp->getTask();   //从共享任务队列取出到自己手里
            }
            task(td->_name);
        }
    }

    //将指定任务放进队列
    void pushTask(const T& task)
    {
        lockGuard lockguard(&lock);
        _task_queue.push(task);
        pthread_cond_signal(&cond);
    }

    void show()
    {

    }

    ~ThreadPool()
    {
        for(auto& iter : _threads)
        {
            iter->join();
            delete[] iter;
        }
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
    }

private:
    std::vector<Thread*> _threads; //线程列表
    int _num;   //线程数量
    std::queue<T> _task_queue;
    pthread_mutex_t lock;
    pthread_cond_t cond;
};