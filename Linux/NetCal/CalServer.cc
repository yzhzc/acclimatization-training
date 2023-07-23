#include "TcpServer.hpp"
#include "Protocol.hpp"
#include <signal.h>

static void Usage(const std::string& process)
{
    std::cout << "\nUsage: "<< process << " port\n" << std::endl;
}

static Response calculatorHelp(const Request& req)
{
    Response resp;
    switch(req.op_)
    {
    case '+':
        resp.result_ = req.x_ + req.y_;
        break;
    case '-':
        resp.result_ = req.x_ - req.y_;
        break;
    case '*':
        resp.result_ = req.x_ * req.y_;
        break;
    case '/':
        if(req.y_ == 0)
            resp.code_ = 1;
        else
            resp.result_ = req.x_ / req.y_;

        break;
    case '%':
        if(req.y_ == 0)
            resp.code_ = 2;
        else
            resp.result_ = req.x_ % req.y_;
        break;
    default:
        resp.code_ = 3;
        break;
    }

    return resp;
}

void debug(int sock)
{
    std::cout << "测试,得到sockfd: " << sock << std::endl;
}

void calculator(int sockfd)
{
    while(1)
    {
        std::string str = Recv(sockfd); //读数据(字符串)
        if(str.empty())
            return;

        Request req;
        req.Deserialized(str);  //字符串反序列化
        Response resp = calculatorHelp(req);    //计算
        std::string respString = resp.Serialise();  //数据序列化
        Send(sockfd, respString);   //写数据
    }
}

// void handler(int signo)
// {
//     std::cout << "得到信号: " << signo << std::endl;
//     exit(0);
// }


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        Usage(argv[0]);
        exit(1);
    }

    //在写入客户端时,对方关闭,send产生SIGPIPE信号,设置忽略
    signal(SIGPIPE, SIG_IGN);

    std::unique_ptr<TcpServer> server(new TcpServer(atoi(argv[1])));
    server->BindHander(calculator);
    server->Start();

    return 0;
}