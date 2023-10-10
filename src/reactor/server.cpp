#include "server.h"
#include "reactor.h"
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>

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

            //构建新的channel 并使用slave—reactor 监听该fd
            std::shared_ptr<Channel> channel = std::make_shared<Channel>(accept_fd);
            slave->_epollpoller->epoll_add(channel, 0);
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