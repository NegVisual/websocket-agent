#include <unistd.h>
#include "httpRequest.h"

namespace websocketagent {
namespace reactor {
    HttpRequest::HttpRequest(std::shared_ptr<SlaveFDReactor> reactor, int connfd) 
        : _reactor(reactor), _fd(connfd) {
        _channel = std::make_shared<Channel>(_fd);
        _channel->setReadHandler(std::bind(&HttpRequest::handleRead, this));
        _channel->setWriteHandler(std::bind(&HttpRequest::handleWrite, this));
        _channel->setConnHandler(std::bind(&HttpRequest::handleConn, this));
    }

    void HttpRequest::handleRead() {
        std::cout << "HttpRequest::handleRead. thread_id: " << std::this_thread::get_id() << std::endl;
        //读取 socket
        while(true) {
            // 从套接字中读取数据
            char buffer[1024];
            int bytesRead;
            std::cout << "===================================" << std::endl;
            bytesRead = recv(_fd, buffer, sizeof(buffer), 0);
            std::cout << buffer <<std::endl;
        }
    }

    void HttpRequest::handleWrite() {
        std::cout << "HttpRequest::handleWrite" << std::endl;
    }

    void HttpRequest::handleConn() {
        std::cout << "HttpRequest::handleConn" << std::endl;
    }

    void HttpRequest::newEvent() {
        std::cout << "HttpRequest::newEvent" << std::endl;
        _channel->setEvents(EPOLLIN | EPOLLET | EPOLLONESHOT);
        _reactor->_epollpoller->epoll_add(_channel, 0);
    }
}
}