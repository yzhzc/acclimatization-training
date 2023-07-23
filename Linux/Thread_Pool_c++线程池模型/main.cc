#include "threadPool.hpp"
#include "Task.hpp"
#include <ctime>
#include <iostream>
#include <cstdlib>


int main()
{
    srand((unsigned long long)time(nullptr) ^ getpid());
    ThreadPool<Task>* tp = new ThreadPool<Task>();
    tp->run();

    while(1)
    {
        int x = rand() % 100 + 1;
        usleep(rand() % 5000 + 1);
        int y = rand() % 30 + 1;
        Task t(x, y, [](int x, int y)->int{
            return x + y;
        });

        std::cout << "制作任务完成" << x << "+" << y << "=" << std::endl;

        tp->pushTask(t);
        sleep(1);
    }

    return 0;
}