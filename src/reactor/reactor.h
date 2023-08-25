#pragma once
#include <memory>
#include "singleton.h"

namespace websocketagent {
namespace reactor {

class FDReactor {
    public:
        FDReactor();
        virtual ~FDReactor();

        EpollPoller();
    private:
};

class MainFDReactor : public websocketagent::base::Singleton<MainFDReactor>, public FDReactor {};

typedef std::shared_ptr<FDReactor> FDReactorPtr;
} // namespace websocketagent    
} // namespace reactor