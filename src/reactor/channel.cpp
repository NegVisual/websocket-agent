#include "channel.h"

namespace websocketagent {
namespace reactor {
    Channel::Channel(FDReactorPtr reactor, int fd)
    : _reactor(reactor), _fd(fd) {}

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
            handleRead();
        }
        if (_receive_event & EPOLLOUT) {
            handleWrite();
        }
        handleConn();
    }
}
}