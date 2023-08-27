#pragma once
#include <memory>
#include "singleton.h"
#include "epollPoller.h"

namespace websocketagent {
namespace reactor {

class FDReactor {
    public:
        FDReactor();

        virtual ~FDReactor();

        void init();
        
    private:
        int32_t createEventfd();

        epollPollerPtr epollpoller;
        int _event_fd;
        int _epoll_fd;
        int _timer_fd;
};

class MainFDReactor : public websocketagent::base::Singleton<MainFDReactor>, public FDReactor {};

typedef std::shared_ptr<FDReactor> FDReactorPtr;
} // namespace websocketagent    
} // namespace reactor