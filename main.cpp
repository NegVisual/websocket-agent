#include <sys/timerfd.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main() {
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (timer_fd == -1) {
        perror("timerfd_create");
        return 1;
    }

    // 设置定时器超时时间和间隔为5秒
    struct itimerspec new_time;
    new_time.it_value.tv_sec = 5;
    new_time.it_value.tv_nsec = 0;
    new_time.it_interval.tv_sec = 5;
    new_time.it_interval.tv_nsec = 0;

    if (timerfd_settime(timer_fd, 0, &new_time, NULL) == -1) {
        perror("timerfd_settime");
        close(timer_fd);
        return 1;
    }

    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        close(timer_fd);
        return 1;
    }

    struct epoll_event event;
    event.data.fd = timer_fd;
    event.events = EPOLLIN;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &event) == -1) {
        perror("epoll_ctl");
        close(timer_fd);
        close(epoll_fd);
        return 1;
    }

    while (1) {
        struct epoll_event events[1];
        int num_events = epoll_wait(epoll_fd, events, 1, -1);
        if (num_events == -1) {
            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == timer_fd) {
                uint64_t expirations;
                if (read(timer_fd, &expirations, sizeof(uint64_t)) == sizeof(uint64_t)) {
                    printf("Timer expired!\n");
                }
            }
        }
    }

    close(timer_fd);
    close(epoll_fd);

    return 0;
}
