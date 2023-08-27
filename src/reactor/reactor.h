#pragma once
#include <memory>
#include "singleton.h"
#include "epollPoller.h"

namespace websocketagent {
namespace reactor {

class FDReactor {
    public:
        FDReactor();
        virtual ~FDReactor();

    private:
        epollPollerPtr epollpoller;
};

class MainFDReactor : public websocketagent::base::Singleton<MainFDReactor>, public FDReactor {};

typedef std::shared_ptr<FDReactor> FDReactorPtr;
} // namespace websocketagent    
} // namespace reactor