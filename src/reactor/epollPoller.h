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

    int32_t getEpollFd() {
        return _epoll_fd;
    }

    poll(ChannelList* activeChannels, int32_t timeout);

private:
    int _epoll_fd;
};

epollPoller::epollPoller(/* args */)
{
    _epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    assert(_epoll_fd > 0);
}

epollPoller::~epollPoller()
{
}

typedef std::shared_ptr<epollPoller> epollPollerPtr;
}    
}
