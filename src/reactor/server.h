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
        void start();

        void setListenFd(int32_t listenfd);

        void setAcceptChannel(std::shared_ptr<Channel> acceptChannel);
    private:
        int _reactorNum;
        int32_t _listenfd;
        std::shared_ptr<Channel> _acceptChannel;
        std::unique_ptr<SlaveFDReactorPool> _slaveFDReactorPool;
};

}
}