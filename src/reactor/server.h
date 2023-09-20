#pragma once
#include <memory>
#include "channel.h"
#include "reactor.h"

namespace websocketagent {
namespace reactor {


typedef std::vector<std::shared_ptr<SlaveFDReactor>> SlaveFDReactorPool;

class Server {
    public:
        Server(int reactorNum);
    private:
        int _reactorNum;
        int _listenfd;
        std::shared_ptr<Channel> acceptChannel_;
        std::unique_ptr<SlaveFDReactorPool> _slaveFDReactorPool;
};

}
}