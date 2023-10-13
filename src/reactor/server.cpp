#include "server.h"
#include "reactor.h"
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "httpRequest.h"

namespace websocketagent {
namespace reactor {
    Server::Server(int reactorNum): _reactorNum(reactorNum) {
        _slaveFDReactorPoolPtr = std::make_shared<ReactorThreadPool>(reactorNum);
        //设置listenFd
        setListenFd(MainFDReactor::getInstance()->getListenFd());
        //设置acceptChannel
        setAcceptChannel(MainFDReactor::getInstance()->getAcceptChannel());
    }

    void Server::handNewConn() {
        std::cout << "Server::handNewConn" << std::endl;
        struct sockaddr_in client_addr;
        memset(&client_addr, 0, sizeof(struct sockaddr_in));
        socklen_t client_addr_len = sizeof(client_addr);
        int accept_fd = 0;
        if ((accept_fd = accept(_listenfd, (struct sockaddr *)&client_addr,
                             &client_addr_len)) > 0) {
            //accept 新的连接
            std::shared_ptr<SlaveFDReactor> slave = _slaveFDReactorPoolPtr->getNextSlaveReactor();
            std::cout << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) <<std::endl;

            // 不能在主线程中 对slave_reactor 直接使用 epoll_add  因为主线程 和 子线程同时操作同一个fd 会产生静态条件 
            // 可以将事件放入队列中 在slave_reactor 对应的 子线程运行时 从队列中取出事件 然后再屌用epoll_add 监听
            std::shared_ptr<HttpRequest> http_request = std::make_shared<HttpRequest>(slave, accept_fd);
            slave->pushEvent(std::bind(&HttpRequest::newEvent, http_request));
                        
            _acceptChannel->setEvents(EPOLLIN | EPOLLET);
        }else {
            std::cout << "Connection failed from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port) <<std::endl;
        }

    }

    void Server::handThisConn() {
        std::cout << "Server::handThisConn" << std::endl;
    }

    void Server::start() {
        _acceptChannel->setReadHandler(std::bind(&Server::handNewConn, this));
        _acceptChannel->setConnHandler(std::bind(&Server::handThisConn, this));
        _slaveFDReactorPoolPtr->start();
        MainFDReactor::getInstance()->loop();
    }

    void Server::setListenFd(int32_t listenfd) {
        _listenfd = listenfd;
    }

    void Server::setAcceptChannel(std::shared_ptr<Channel> acceptChannel) {
        _acceptChannel = acceptChannel;
    }
}
}