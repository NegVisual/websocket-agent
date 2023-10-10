#include "reactor.h"
#include <sys/eventfd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <memory>

namespace websocketagent {
namespace reactor {
    int32_t FDReactor::createEventfd()
    {
        int32_t evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
        if (evtfd < 0)
        {
            abort();
        }
        return evtfd;
    }

    std::shared_ptr<FDReactor> FDReactor::alloc() {
        std::shared_ptr<FDReactor> ret(new(std::nothrow) FDReactor());
        ret->_self_ptr = ret;
        return ret;
    }

    void FDReactor::loop() {
        ChannelList active_events;

        while(true) {
            active_events = _epollpoller->poll();

            _eventHandling = true;
            for (auto& it : active_events) {
                std::cout << "epoll return" << std::endl;
                it->handleEvents();
           }
           _eventHandling = false;
        }
    }

    FDReactor::~FDReactor() {}

    void SlaveFDReactor::init(int thread_index) {
        _epollpoller = std::make_shared<EpollPoller>(_self_ptr.lock());
        if(_epollpoller.get() != nullptr) {
            _epoll_fd = _epollpoller->getEpollFd();
        } else {
            abort();
        }
        _event_fd = createEventfd();

        _slave_thread = std::make_shared<SlaveThread>(std::bind(&SlaveFDReactor::loop, this) ,thread_index);

        _slave_thread->setReactor(shared_from_this());
    };

    void SlaveFDReactor::run() {
        _slave_thread->start();
    }

    void MainFDReactor::init(uint16_t port) {
        _epollpoller = std::make_shared<EpollPoller>(_self_ptr.lock());
        if(_epollpoller.get() != nullptr) {
            _epoll_fd = _epollpoller->getEpollFd();
            std::cout << "MainFDReactor::init success! epoll_fd:" << _epoll_fd << std::endl;
        } else {
            std::cout << "MainFDReactor::init failed!" << std::endl;
            abort();
        }
        _event_fd = createEventfd();

        //创建acceptor
        _listenfd = socket_bind_listen(port);

        _acceptChannel = std::make_shared<Channel>(_listenfd);
        _acceptChannel->setEvents(EPOLLIN | EPOLLET);
        _epollpoller->epoll_add(_acceptChannel, 0);
    };

    int32_t MainFDReactor::getListenFd() {
        return _listenfd;
    }

    std::shared_ptr<Channel> MainFDReactor::getAcceptChannel() {
        return _acceptChannel;
    }

    int MainFDReactor::socket_bind_listen(int port) {
        // 检查port值，取正确区间范围
        if (port < 0 || port > 65535) return -1;

        // 创建socket(IPv4 + TCP)，返回监听描述符
        int listen_fd = 0;
        if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) return -1;

        // 消除bind时"Address already in use"错误
        int optval = 1;
        if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval,
                        sizeof(optval)) == -1) {
            close(listen_fd);
            return -1;
        }

        // 设置服务器IP和Port，和监听描述副绑定
        struct sockaddr_in server_addr;
        bzero((char *)&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        server_addr.sin_port = htons((unsigned short)port);
        if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
            -1) {
            close(listen_fd);
            return -1;
        }

        // 开始监听，最大等待队列长为LISTENQ
        if (listen(listen_fd, 2048) == -1) {
            close(listen_fd);
            return -1;
        }

        // 无效监听描述符
        if (listen_fd == -1) {
            close(listen_fd);
            return -1;
        }
        return listen_fd;
    }
}
}