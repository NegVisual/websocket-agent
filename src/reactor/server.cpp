#include "server.h"

namespace websocketagent {
namespace reactor {
    Server::Server(int reactorNum): _reactorNum(reactorNum) {
         // 使用 std::make_unique 初始化 _slaveFDReactorPool
        _slaveFDReactorPool = std::make_unique<SlaveFDReactorPool>(_reactorNum);

        // 初始化 _slaveFDReactorPool 中的元素（如果需要）
        for (int i = 0; i < _reactorNum; ++i) {
            auto slave_reactor = std::make_shared<SlaveFDReactor>();
            slave_reactor->init();
            // 还可以执行其他初始化操作
            _slaveFDReactorPool->at(i) = slave_reactor;
        }
    }
}
}