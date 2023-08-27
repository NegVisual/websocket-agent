#include "reactor.h"

namespace websocketagent {
namespace reactor {
    FDReactor::FDReactor() {
        epollpoller = std::make_shared<epollPoller>();
    }

    FDReactor::~FDReactor() {}
}
}