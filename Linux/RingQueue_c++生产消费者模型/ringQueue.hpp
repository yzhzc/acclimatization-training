#ifndef __Ring_QUEUE_HPP__
#define __Ring_QUEUE_HPP__

#include <iostream>
#include <vector>
#include <pthread.h>
#include "sem.hpp"


const int g_default_num = 5;

template<class T>
class RingQueue
{
public:
    void test()
    {
        std::cout << "hello world" << std::endl;
    }

    RingQueue(int default_num = g_default_num)
        :ring_queue_(default_num)
        ,num_(default_num)
        ,space_sem_(default_num)
        ,data_sem_(0)
    {
        pthread_mutex_init(&clock, nullptr);
        pthread_mutex_init(&plock, nullptr);
    }

    ~RingQueue()
    {
        pthread_mutex_destroy(&clock);
        pthread_mutex_destroy(&plock);
    }

    //生产
    void push(const T& in)
    {
        
        space_sem_.P();
        pthread_mutex_lock(&plock);
        
        ring_queue_[p_step++] = in;
        p_step %= num_;

        pthread_mutex_unlock(&plock);
        data_sem_.V();
        
    }

    //消费
    void pop(T *out)
    {
        data_sem_.P();
        pthread_mutex_lock(&clock);
        
        *out = ring_queue_[c_step++];
        c_step %= num_;
        
        pthread_mutex_unlock(&clock);
        space_sem_.V();
    }

    void debug()
    {
        std::cout << "size: " << ring_queue_.size() << " num: " << num_ << std::endl;
    }

private:
    std::vector<T> ring_queue_;
    int num_;
    int c_step; //消费下标
    int p_step; //生产下标
    Sem space_sem_; //容量
    Sem data_sem_;  //库存
    pthread_mutex_t clock;  //
    pthread_mutex_t plock;  //
};

#endif