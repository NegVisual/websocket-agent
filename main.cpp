#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "reactor.h"

int main() {
    websocketagent::reactor::MainFDReactor::getInstance().init();
}
