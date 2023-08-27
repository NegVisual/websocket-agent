#pragma once

#include <sys/epoll.h>
#include <sys/socket.h>
#include <assert.h>
#include <memory>

namespace websocketagent {
namespace reactor {

class epollPoller
{
private:
    /* data */
public:
    epollPoller(/* args */);
    ~epollPoller();
private:
    int epollFd_;
};

epollPoller::epollPoller(/* args */)
{
    epollFd_ = epoll_create1(EPOLL_CLOEXEC);
    assert(epollFd_ > 0);
}

epollPoller::~epollPoller()
{
}

typedef std::shared_ptr<epollPoller> epollPollerPtr;
}    
}
