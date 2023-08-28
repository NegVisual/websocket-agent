#include "epollPoller.h"
#include <unistd.h>

namespace websocketagent {
namespace reactor {

EpollPoller::EpollPoller()
{
    _epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    assert(_epoll_fd > 0);
}

EpollPoller::~EpollPoller()
{
    close(_epoll_fd);
}

void EpollPoller::poll(ChannelList* activeChannels, int32_t timeout) {

}

}
}