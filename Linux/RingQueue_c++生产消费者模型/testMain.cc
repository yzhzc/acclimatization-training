#include "ringQueue.hpp"
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <unistd.h>


//消费
void* consumer(void *args)
{
    RingQueue<int> *rq = (RingQueue<int> *)args;
    while(1)
    {
        // sleep(2);
        //获取数据或者任务对象
        int x = -1;
        
        //环形队列中取出
        rq->pop(&x);
        std::cout << "消费:" << x << std::endl;
        
    }
}

//生产
void* productor(void *args)
{
    RingQueue<int> *rq = (RingQueue<int> *)args;
    while(1)
    {
        // sleep(0.5);

        //构建数据或者任务对象
        int x = rand() % 100 + 1;
         
        //推送到环形队列中

        rq->push(x++);
        std::cout << "    生产:" << x << std::endl;
    }
}




int main(int argc, char *argv[])
{
    srand((uint64_t)time(nullptr) ^ getpid());
    RingQueue<int> *rq = new RingQueue<int>(5);
    rq->debug();

    int count = 3;
    pthread_t c[count], p[count];
    for(int i = 0; i < count; i++)
    {
        pthread_create(&c[i], nullptr, consumer, (void *)rq);
        pthread_create(&p[i], nullptr, productor, (void *)rq);
    }
    
    for(int i = 0; i < count; i++)
    {
        pthread_join(c[i], nullptr);
        pthread_join(p[i], nullptr);
    }
    



    return 0;
}