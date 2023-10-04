#pragma once
#include <memory>
#include <unordered_map>
#include "singleton.h"
#include "epollPoller.h"
#include "slaveThread.h"
namespace websocketagent {
namespace reactor {

class EpollPoller;
typedef std::shared_ptr<EpollPoller> EpollPollerPtr;

class SlaveThread;

class Channel;
class AcceptChannel;
typedef std::shared_ptr<Channel> ChannelPtr;

class FDReactor {
    typedef std::weak_ptr<FDReactor> FDReactorWeakPtr;
    public:
        FDReactor() {};

        static std::shared_ptr<FDReactor> alloc();

        virtual ~FDReactor();

        void loop();

        EpollPollerPtr _epollpoller;
    private:

    protected:
        int32_t createEventfd();
        FDReactorWeakPtr _self_ptr; 
        int _event_fd;
        int _epoll_fd;
        int _timer_fd;
        std::unordered_map<int, ChannelPtr> _fd2channel;

        bool _eventHandling;
};

class SlaveFDReactor : public FDReactor, public std::enable_shared_from_this<SlaveFDReactor> {
    public:
        void init();

        void run();
    private:
        std::shared_ptr<SlaveThread> _slave_thread;
};

class MainFDReactor : public Singleton<MainFDReactor>, public FDReactor {
    public:
        void init(uint16_t port);

        int32_t getListenFd();

        std::shared_ptr<Channel> getAcceptChannel();
    private:
        int32_t socket_bind_listen(int port);
    private:
        std::shared_ptr<Channel> _acceptChannel;
        int32_t _listenfd;
};

typedef std::vector<std::shared_ptr<SlaveFDReactor>> SlaveFDReactorPool;

} // namespace websocketagent    
} // namespace reactor