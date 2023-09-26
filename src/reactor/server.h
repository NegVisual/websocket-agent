#pragma once
#include <memory>
#include "channel.h"
#include "reactorPool.h"

namespace websocketagent {
namespace reactor {

class Server {
    public:
        Server(int reactorNum);
        void start();

        void setListenFd(int32_t listenfd);

        void setAcceptChannel(std::shared_ptr<Channel> acceptChannel);

        void handNewConn();

        void handThisConn();
    private:
        int _reactorNum;
        int32_t _listenfd;
        std::shared_ptr<Channel> _acceptChannel;
        std::shared_ptr<ReactorThreadPool> _slaveFDReactorPoolPtr;
};

}
}