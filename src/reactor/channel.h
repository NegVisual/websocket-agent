#pragma once
#include <functional>
#include "reactor.h"

namespace websocketagent {
namespace reactor {

class FDReactor;
typedef std::shared_ptr<FDReactor> FDReactorPtr;
typedef std::function<void()> CallBack;

class Channel {
    public:
        explicit Channel(FDReactorPtr reactor, int fd);
        
        ~Channel();

        int getFd();

        void setFd(int fd);

        int getEvents() const { 
            return _events; 
        }

        void setEvents(int event) { 
            _events = event; 
        }

        int getReceiveEvent() const { 
            return _receive_event; 
        }

        void setReceiveEvent(int receiveEvent) { 
            _receive_event = receiveEvent; 
        }

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
        int _events;        //epoll 需要监听的事件类型
        int _receive_event; //事件发生时，真实的事件类型

        FDReactorPtr _reactor;
        int _fd;
        CallBack _readHandler;
        CallBack _writeHandler;
        CallBack _errorHandler;
        CallBack _connHandler;
};

}
}