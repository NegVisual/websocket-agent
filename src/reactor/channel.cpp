#include "channel.h"

namespace websocketagent {
namespace reactor {
    Channel::Channel(FDReactorPtr reactor, int fd)
    : _reactor(reactor), _fd(fd) {}

    Channel::~Channel() {}

    int Channel::getFd() { return _fd; }

    void Channel::setFd(int fd) { _fd = fd; }

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
}
}