#pragma once

#include <iostream>
#include <pthread.h>

class Mutex
{
public:
    Mutex(pthread_mutex_t *mtx)
        :pmtx_(mtx)
    {}
    void lock() 
    {
        //std::cout << "进行加锁" << std::endl;
        pthread_mutex_lock(pmtx_);
    }
    void unlock()
    {
        //std::cout << "进行解锁" << std::endl;
        pthread_mutex_unlock(pmtx_);
    }
    ~Mutex()
    {}
private:
    pthread_mutex_t *pmtx_;
};

// RAII风格的加锁方式
class lockGuard
{
public:
    lockGuard(pthread_mutex_t *mtx)
        :mtx_(mtx)
    {
        mtx_.lock();
    }
    ~lockGuard()
    {
        mtx_.unlock();
    }
private:
    Mutex mtx_;
};
