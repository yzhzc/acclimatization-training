#pragma once

#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <string>
#include <cstring>

// 日志是有日志级别的
#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4

const char *gLevelMap[] = {
    "DEBUG",   // 调试
    "NORMAL",  // 正常
    "WARNING", // 警告
    "ERROR",   // 错误
    "FATAL"};  // 致命

#define LOGFILE "./selectServer.log"

// 完整的日志功能，至少: 日志等级 时间 支持用户自定义(日志内容, 文件行，文件名)
void logMessage(int level, const char *format, ...)
{
    // va_list ap;
    // va_start(ap, format);
    // while()
    // int x = va_arg(ap, int);
    // va_end(ap); //ap=nullptr
    char stdBuffer[1024]; // 标准部分
    time_t timestamp = time(nullptr);
    // struct tm *localtime = localtime(&timestamp);
    snprintf(stdBuffer, sizeof stdBuffer, "[%s] [%ld] ",
             gLevelMap[level], timestamp);

    char logBuffer[1024]; // 自定义部分
    va_list args;
    va_start(args, format);
    // vprintf(format, args);
    vsnprintf(logBuffer, sizeof logBuffer, format, args);
    va_end(args);

    // FILE *fp = fopen(LOGFILE, "a");
    printf("%s%s\n", stdBuffer, logBuffer);
    // fprintf(fp, "%s%s\n", stdBuffer, logBuffer);
    // fclose(fp);
}