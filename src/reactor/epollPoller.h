#pragma once

#include <sys/epoll.h>
#include <sys/socket.h>
#include <assert.h>
#include <memory>
#include "channel.h"

namespace websocketagent {
namespace reactor {

class Channel;
typedef std::vector<Channel*> ChannelList;

class EpollPoller
{
    public:
        EpollPoller();
        ~EpollPoller();

        int32_t getEpollFd() {
            return _epoll_fd;
        }

        void poll(ChannelList* activeChannels, int32_t timeout);

        void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    private:
        int _epoll_fd;
};
}    
}
