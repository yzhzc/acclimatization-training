#include <memory>
#include "TcpServer.hpp"
#include "Protocol.hpp"

static Response calculator(const Request &req)
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

void NetCal(Connection *conn, std::string &request)
{
    //1. 反序列化
    Request req;
    if(!req.Deserialized(request))
        return;
    //2. 业务处理
    Response resp = calculator(req);
    //3. 序列化,构建答应
    std::string sendstr = resp.Serialise();
    sendstr = Encode(sendstr);
    //4. 交给服务器发送缓冲区
    conn->_outbuffer += sendstr;
    //5. 打开服务器发送模块,发送发送缓冲区内容
    conn->_tsvr->EnableReadWrite(conn, true, true);
    
}

int main()
{
    std::unique_ptr<TcpServer> svr(new TcpServer());
    svr->Dispather(NetCal);

    return 0;
}