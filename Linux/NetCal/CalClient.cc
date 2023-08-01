#include <iostream>
#include "Sock_yzhzc.hpp"
#include "Protocol.hpp"

static void Usage(const std::string &process)
{
    std::cout << "\nUsage: " << process << " serverIp serverPort\n"
              << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }

    std::string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);
    Sock sock;
    int sockfd = sock.Socket();

    if (!sock.Connect(sockfd, server_ip, server_port))
    {
        std::cerr << "Connect error" << std::endl;
        exit(2);
    }

    bool quit = true;
    while (quit)
    {
        // 1. 用户输入
        Request req;
        std::cout << "请输入x # y" << std::endl;
        std::cin >> req.x_ >> req.op_ >> req.y_;
        // 2. 序列化
        std::string s = req.Serialise();
        // 3. 添加序列化报头报尾
        s = Encode(s);
        // 4. 写数据
        Send(sockfd, s);
        std::string buffer;
        while (1)
        {
            //5. 读数据
            int res = Recv(sockfd, buffer);
            if (!res)
            {
                quit = false;
                break;
            }
            //6. 判断接收的报文是否完整
            std::string package = Decode(buffer);
            if (package.empty())
                continue;

            //7. 反序列化
            Response resp;
            resp.Deserialized(package);
            std::cout << "code:" << resp.code_ << std::endl;
            std::cout << "result:" << resp.result_ << std::endl;
            break;
        }
    }
    close(sockfd);
    return 0;
}