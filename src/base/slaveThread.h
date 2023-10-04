#pragma once
#include <functional>
#include <thread>
#include <string>
#include <memory>
#include "noncopyable.h"
#include "reactor.h"

namespace websocketagent {
namespace reactor {
typedef std::function<void()> ThreadFunc;

class SlaveFDReactor;

class SlaveThread : public Noncopyable {
    public:
        explicit SlaveThread(const ThreadFunc&, const std::string& name = "");

        ~SlaveThread();

        void start();

        void runInThread();

        void setReactor(std::shared_ptr<SlaveFDReactor> reactor);
    private:
        std::thread _thread;
        ThreadFunc _func;
        std::thread::id _thread_id; //线程id
        pid_t _pid; //进程id
        std::string _name;
        bool _started;
        bool _joined;
        std::shared_ptr<SlaveFDReactor> _reactor;
};
}
}