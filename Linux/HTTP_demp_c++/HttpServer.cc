#include <iostream>
#include <memory>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <fstream>
#include "HttpServer.hpp"
#include "Usage.hpp"
#include "Util.hpp"

#define ROOT "./wwwroot"
#define HOMEPAGE "index.html"

void HandlerHttpRequest(int sockfd)
{
    // 1. 读取请求
    char buffer[1024 * 10];
    std::cout << "开始接收\n"
              << std::endl;

    ssize_t n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
    if (n > 0)
    {
        buffer[n] = 0;
        // std::cout << buffer << "-----------\n" << std::endl;
    }
    // 1. 报文切片
    std::vector<std::string> vline;
    Util::cutString(buffer, "\r\n", vline);
    // 2. 提取地址行
    std::vector<std::string> vblock;
    Util::cutString(vline[0], " ", vblock);
    // 3. 获取访问地址
    std::string file = vblock[1];
    if(file == "/")
        file = "/index.html";

    file = ROOT + file;
    std::cout << file << std::endl;
    // 4. 打开访问的文件
    std::ifstream in(file);
    std::string content;
    // 5.读取文件内容
    if (in.is_open())
    {
        std::string line;
        while(std::getline(in, line))
        {
            content += line;
        }
        in.close();
    }
    // 6.发送文件内容,浏览器会解析你发送的报文
    std::string HttpResponse;
    if(content.empty())
    {
        HttpResponse = "HTTP/1.1 302 Found\r\n";
        HttpResponse += "Location: https://leetcode.cn/u/a-er-nu/";
    }
        
    else
    {
        HttpResponse = "HTTP/1.1 200 OK\r\n";
        
    }
        

    HttpResponse += "\r\n";
    HttpResponse += content;
    send(sockfd, HttpResponse.c_str(), HttpResponse.size(), 0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(0);
    }
    std::unique_ptr<HttpServer> httpServer(new HttpServer(atoi(argv[1]), HandlerHttpRequest));
    httpServer->Start();

    return 0;
}