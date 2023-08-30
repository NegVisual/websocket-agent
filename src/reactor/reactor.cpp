#include "reactor.h"
#include <sys/eventfd.h>

namespace websocketagent {
namespace reactor {

    int32_t FDReactor::createEventfd()
    {
        int32_t evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
        if (evtfd < 0)
        {
            abort();
        }
        return evtfd;
    }

    std::shared_ptr<FDReactor> FDReactor::alloc() {
        std::shared_ptr<FDReactor> ret(new(std::nothrow) FDReactor());
        ret->_self_ptr = ret;
        return ret;
    }

    FDReactor::~FDReactor() {}
}
}