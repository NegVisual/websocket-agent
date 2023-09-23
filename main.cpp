#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include "reactor.h"
#include "server.h"

int main() {
    int port = 3581;
    int slave_number = 5;
    websocketagent::reactor::MainFDReactor::getInstance()->init(port);
    websocketagent::reactor::Server server(slave_number); //服务启动 增加slave reactor
    server.start();
    while (true) {
        
    }
    return 0;
}
