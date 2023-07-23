#include <iostream>
#include "Sock_yzhzc.hpp"
#include "Protocol.hpp"

static void Usage(const std::string& process)
{
    std::cout << "\nUsage: "<< process << " serverIp serverPort\n" << std::endl;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }

    std::string server_ip = argv[1];
    uint16_t server_port = atoi(argv[2]);
    Sock sock;
    int sockfd = sock.Socket();
    
    if(!sock.Connect(sockfd, server_ip, server_port))
    {
        std::cerr << "Connect error"<< std::endl;
        exit(2);
    }

    while(1)
    {

        Request req;
        std::cout << "请输入x:" << std::endl;
        std::cin >> req.x_;
        std::cout << "请输入y:" << std::endl;
        std::cin >> req.y_;
        std::cout << "请输入操作符#:" << std::endl;
        std::cin >> req.op_;
        
        std::string s = req.Serialise();
        Send(sockfd, s);
        std::string r = Recv(sockfd);
        Response resp;
        resp.Deserialized(r);
        std::cout << "code:" << resp.code_ << std::endl;
        std::cout << "result:" << resp.result_ << std::endl;
        sleep(1);
    }

    return 0;
}