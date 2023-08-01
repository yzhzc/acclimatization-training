#include "TcpServer.hpp"
#include "Protocol.hpp"
#include "Daemon.hpp"
#include <signal.h>

static void Usage(const std::string &process)
{
    std::cout << "\nUsage: " << process << " port\n"
              << std::endl;
}

static Response calculatorHelp(const Request &req)
{
    Response resp;
    switch (req.op_)
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
        if (req.y_ == 0)
            resp.code_ = 1;
        else
            resp.result_ = req.x_ / req.y_;

        break;
    case '%':
        if (req.y_ == 0)
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
    std::string inbuffer;
    while (1)
    {
        // 1. 读数据(字符串)
        bool res = Recv(sockfd, inbuffer);
        if (!res)
            return;

        // 2. 解析报文
        std::string package = Decode(inbuffer);
        // 3. 保证是一个完整报文
        if (package.empty())
            continue;

        logMessage(NORMAL,"s", package.c_str());
        // 4. 字符串反序列化
        Request req;
        bool ret = req.Deserialized(package);
        if(!ret)
        {
            std::cout << "Deserialized失败" << std::endl;
            exit(0);
        }         
        // 5. 计算
        Response resp = calculatorHelp(req);
        // 6. 数据序列化
        std::string respString = resp.Serialise();
        // 7. 添加序列化报头报尾
        respString = Encode(respString);
        // 8. 写数据
        Send(sockfd, respString);
        std::cout << "写入成功" << std::endl;

    }
}

// void handler(int signo)
// {
//     std::cout << "得到信号: " << signo << std::endl;
//     exit(0);
// }

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        Usage(argv[0]);
        exit(1);
    }

    // 在写入客户端时,对方关闭,send产生SIGPIPE信号,设置忽略
    //signal(SIGPIPE, SIG_IGN);
    //MyDaemon();
    std::unique_ptr<TcpServer> server(new TcpServer(atoi(argv[1])));
    server->BindHander(calculator);
    server->Start();

    return 0;
}