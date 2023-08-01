#pragma once

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void MyDaemon()
{
    // 1. 忽略信号，SIGPIPE，SIGCHLD
    signal(SIGPIPE, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);

    // 2. 不要让自己成为组长
    if (fork() > 0)
        return;
    // 3. 调用setsid
    setsid();
    // 4. 标准输入，标准输出，标准错误的重定向,守护进程不能直接向显示器打印消息
    int devnull = open("/dev/null", O_RDONLY | O_WRONLY);
    if(devnull > 0)
    {
        dup2(0, devnull);
        dup2(1, devnull);
        dup2(2, devnull);
        close(devnull);
    }
}