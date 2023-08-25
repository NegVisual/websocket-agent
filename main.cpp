#include <iostream>
#include <thread>
#include <sys/eventfd.h>
#include <unistd.h>

void threadFunction(int threadId) {
    std::cout << "Thread " << threadId << " started." << std::endl;

    // Create eventfd file descriptor
    int efd = eventfd(0, EFD_NONBLOCK);
    if (efd == -1) {
        perror("eventfd");
        return;
    }

    std::cout << "ThreadId: " << threadId << ", efd value:"  << efd << " finished." << std::endl;
}

int main() {
    std::thread threads[5];

    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(threadFunction, i);
    }

    for (int i = 0; i < 5; ++i) {
        threads[i].join();
    }

    return 0;
}
