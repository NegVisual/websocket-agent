#include "reactor.h"

namespace websocketagent {
namespace reactor {

class HttpRequest {
    public:
        HttpRequest(std::shared_ptr<SlaveFDReactor> reactor, int connfd);

        void newEvent();

    
    private:
        int _fd;
        std::shared_ptr<SlaveFDReactor> _reactor;
        std::shared_ptr<Channel> _channel;
        void handleRead();
        void handleWrite();
        void handleConn();
};

}
}