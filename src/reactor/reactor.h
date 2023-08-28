#pragma once
#include <memory>
#include "singleton.h"
#include "epollPoller.h"

namespace websocketagent {
namespace reactor {

class EpollPoller;
typedef std::shared_ptr<EpollPoller> EpollPollerPtr;

class FDReactor {
    public:
        FDReactor();

        virtual ~FDReactor();

        void init() {};

        void init(uint32_t ip, uint16_t port) {};
        
    private:
        int32_t createEventfd();

        EpollPollerPtr epollpoller;
        int _event_fd;
        int _epoll_fd;
        int _timer_fd;
};

class MainFDReactor : public websocketagent::base::Singleton<MainFDReactor>, public FDReactor {};
} // namespace websocketagent    
} // namespace reactor