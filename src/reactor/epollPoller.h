#pragma once

#include <sys/epoll.h>
#include <sys/socket.h>
#include <assert.h>
#include <memory>
#include "channel.h"

namespace websocketagent {
namespace reactor {

class Channel;
typedef std::shared_ptr<Channel> ChannelPtr;
typedef std::vector<ChannelPtr> ChannelList;

class EpollPoller
{
    public:
        EpollPoller();
        ~EpollPoller();

        int32_t getEpollFd() {
            return _epoll_fd;
        }

        ChannelList poll(int32_t timeout);

        void epoll_add(ChannelPtr Channel, int timeout);

        void epoll_mod(ChannelPtr Channel, int timeout);
        
        void epoll_del(ChannelPtr Channel, int timeout);

        void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

    private:
        int _epoll_fd;
};
}    
}
