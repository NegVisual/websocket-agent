#include "channel.h"
#include "reactor.h"

namespace websocketagent {
namespace reactor {
    Channel::Channel(int fd)
    : _fd(fd) {
        std::cout << "Channel::Channel: _reactor:" << (_reactor.get() == nullptr) << std::endl; 
    }


    Channel::~Channel() {}

    int Channel::getFd() { return _fd; }

    void Channel::handleRead() {
        if (_readHandler) {
            _readHandler();
        }
    }

    void Channel::handleWrite() {
        if (_writeHandler) {
            _writeHandler();
        }
    }

    void Channel::handleConn() {
        std::cout << "Channel::handleConn: new connect receeived" <<std::endl;
        if (_connHandler) {
            _connHandler();
        }
    }

    void Channel::handleError() {
        if (_errorHandler) {
            _errorHandler();
        }
    }

    void Channel::handleEvents() {
        _events = 0;
        std::cout << "Channel::handleEvents" << std::endl;
        if ((_receive_event & EPOLLHUP) && !(_receive_event & EPOLLIN)) {
            _events = 0;
            return;
        }
        if (_events & EPOLLERR) {
            if (_errorHandler) handleError();
            _events = 0;
            return;
        }
        if (_events & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
            std::cout << "Channel::handleEvents" << std::endl;
            handleRead();
        }
        if (_receive_event & EPOLLOUT) {
            handleWrite();
        }
        handleConn();
    }
}
}