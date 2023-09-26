#pragma once
#include <iostream>
#include "noncopyable.h"
#include "reactor.h"

namespace websocketagent {
namespace reactor {

class ReactorThreadPool : public websocketagent::base::Noncopyable {
    public:
        ReactorThreadPool(int numThreads);

        ~ReactorThreadPool() { 
            std::cout << "~ReactorThreadPool()" << std::endl;
        }

        std::shared_ptr<SlaveFDReactor> getNextSlaveReactor();

    private:
        int _next;
        int _numThreads;
        SlaveFDReactorPool _fDReactorPool;
};

}
}