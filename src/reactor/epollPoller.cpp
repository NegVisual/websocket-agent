#include "epollPoller.h"
#include <unistd.h>
#include <string.h>

namespace websocketagent {
namespace reactor {

const int EVENTSNUM = 4096;

EpollPoller::EpollPoller(FDReactorPtr reactor) : _reactor(reactor), _epoll_events(EVENTSNUM)
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
    int numEvents = epoll_wait(_epoll_fd, &*_epoll_events.begin(),
        static_cast<int>(_epoll_events.size()), timeout);

    std::cout << "EpollPoller::poll numEvents:" << numEvents << std::endl;

    if (numEvents < 0) perror("epoll wait error");
    
    int savedErrno = errno;

    if (numEvents > 0)
    {
        fillActiveChannels(numEvents, channel_list);
    }else if (numEvents == 0) {
        std::cout << "nothing happened" << std::endl;
    }else {
        // error happens, log uncommon ones
        if (savedErrno != EINTR)
        {
            errno = savedErrno;
            std::cout << "EPollPoller::poll()" << std::endl;
        }
    }
    return channel_list;
}

void EpollPoller::epoll_add(ChannelPtr channel, int timeout) {
    int fd = channel->getFd();
    if (_reactor.get() != nullptr) {
        _reactor->getFd2Channel()[fd] = channel;
    }
    
    struct epoll_event event;
    memset(&event, 0, sizeof event);
    event.events = channel->getEvents();
    event.data.fd = fd;

    if(epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, fd, &event) < 0) {
        perror("epoll_add error");
    }

    return;
}

void EpollPoller::epoll_mod(ChannelPtr Channel, int timeout) {
    return;
}
        
void EpollPoller::epoll_del(ChannelPtr Channel, int timeout) {
    return;
}

void EpollPoller::fillActiveChannels(int numEvents, ChannelList& activeChannels) const
{
    auto channel_list = _reactor->getFd2Channel();
    for (int i = 0; i < numEvents; ++i)
    {
        int fd = _epoll_events[i].data.fd;

        assert(channel_list.find(fd) != channel_list.end());

        auto channel = channel_list[fd];

        channel->setReceiveEvent(_epoll_events[i].events);
        activeChannels.push_back(channel);
    }
}

}
}