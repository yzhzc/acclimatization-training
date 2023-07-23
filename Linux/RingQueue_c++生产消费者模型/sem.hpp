#ifndef __SEM_HPP__
#define __SEM_HPP__

#include <iostream>
#include <semaphore.h>

class Sem
{
public:
    Sem(int value)
    {
        sem_init(&sem_, 0, value);
    }

    ~Sem()
    {
        sem_destroy(&sem_);
    }

    //--
    void P()
    {
        sem_wait(&sem_);
    }

    //++
    void V()
    {
        sem_post(&sem_);
    }

private:
    sem_t sem_;
};



#endif