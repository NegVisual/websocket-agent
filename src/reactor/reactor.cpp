#include "reactor.h"
#include <sys/eventfd.h>

namespace websocketagent {
namespace reactor {
    FDReactor::FDReactor() {
        epollpoller = std::make_shared<EpollPoller>(shared_from_this());
        _epoll_fd = epollpoller->getEpollFd();
        _event_fd = createEventfd();
    }

    int32_t FDReactor::createEventfd()
    {
        int32_t evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
        if (evtfd < 0)
        {
            abort();
        }
        return evtfd;
    }

    FDReactor::~FDReactor() {}
}
}