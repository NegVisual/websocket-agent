#pragma once
#include <functional>
#include "reactor.h"

namespace websocketagent {
namespace reactor {

class FDReactor;
typedef std::function<void()> CallBack;
typedef std::shared_ptr<FDReactor> FDReactorPtr;

class Channel {
    public:
        explicit Channel(FDReactorPtr reactor, int fd);
        
        ~Channel();

        int getFd();

        void setFd(int fd);

        void setReadHandler(CallBack &&readHandler) { 
            _readHandler = readHandler; 
        }

        void setWriteHandler(CallBack &&writeHandler) {
            _writeHandler = writeHandler;
        }

        void setErrorHandler(CallBack &&errorHandler) {
            _errorHandler = errorHandler;
        }

        void setConnHandler(CallBack &&connHandler) { 
            _connHandler = connHandler; 
        }

        void handleRead();

        void handleWrite();

        void handleConn();

        void handleError();

    private:
        FDReactorPtr _reactor;
        int _fd;
        CallBack _readHandler;
        CallBack _writeHandler;
        CallBack _errorHandler;
        CallBack _connHandler;
};

}
}