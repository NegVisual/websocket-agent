#include "epollPoller.h"
#include <unistd.h>
#include <string.h>

namespace websocketagent {
namespace reactor {

EpollPoller::EpollPoller(FDReactorPtr reactor) : _reactor(reactor)
{
    _epoll_fd = epoll_create1(EPOLL_CLOEXEC);
    assert(_epoll_fd > 0);
}

EpollPoller::~EpollPoller()
{
    close(_epoll_fd);
}

ChannelList EpollPoller::poll(int32_t timeout) {
    ChannelList channel_list;
    return channel_list;
}

void EpollPoller::epoll_add(ChannelPtr channel, int timeout) {
    struct epoll_event event;
    memset(&event, 0, sizeof event);
    event.events = channel->getEvents();



    return;
}

void EpollPoller::epoll_mod(ChannelPtr Channel, int timeout) {
    return;
}
        
void EpollPoller::epoll_del(ChannelPtr Channel, int timeout) {
    return;
}

}
}