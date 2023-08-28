#include "epollPoller.h"

namespace websocketagent {
namespace reactor {

EpollPoller::EpollPoller(/* args */)
{
    _epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    assert(_epoll_fd > 0);
}

EpollPoller::~EpollPoller()
{
}

void EpollPoller::poll(ChannelList* activeChannels, int32_t timeout) {

}

}
}