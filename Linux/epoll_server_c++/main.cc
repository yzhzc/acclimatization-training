#include <iostream>
#include <memory>
#include "Epoll_server.hpp"

using namespace std;

void change(string request)
{
    cout << "change : " << request << endl;
}

int main(int argc,char *argv[])
{
    unique_ptr<EpolServer> epoll_server(new EpolServer(change));
    epoll_server->start();


    return 0;
}


