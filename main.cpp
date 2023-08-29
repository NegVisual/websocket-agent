#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#include "reactor.h"

int main() {
    int port = 3581;
    int slave_number = 5;
    websocketagent::reactor::MainFDReactor::getInstance().init(INADDR_ANY, port);
    // Server server(slave_number);
    // server.start();
    return 0;
}
