#include "reactorPool.h"
#include "reactor.h"

namespace websocketagent {
namespace reactor {
    ReactorThreadPool::ReactorThreadPool(int numThreads) : _next(0), _numThreads(numThreads) {
         // 使用 std::make_unique 初始化 _slaveFDReactorPool
        _fDReactorPool = SlaveFDReactorPool(numThreads);

        // 初始化 _slaveFDReactorPool 中的元素
        for (int i = 0; i < numThreads; ++i) {
            auto slave_reactor = std::make_shared<SlaveFDReactor>();
            slave_reactor->init();
            _fDReactorPool.at(i) = slave_reactor;
        }
    }

    std::shared_ptr<SlaveFDReactor> ReactorThreadPool::getNextSlaveReactor() {
        std::shared_ptr<SlaveFDReactor> slave_reactor;
        if (!_fDReactorPool.empty()) {
            slave_reactor = _fDReactorPool[_next];
            _next = (_next + 1) % _numThreads;
            _next = (_next + 1) % _numThreads;
        }

        return slave_reactor;
    }

    void ReactorThreadPool::start() {
        for(auto slave_thread : _fDReactorPool) {
            slave_thread->run();
        }
    }
}
}