#pragma once
#include <functional>
#include <thread>
#include <string>
#include "noncopyable.h"

namespace websocketagent {
namespace base {
typedef std::function<void()> ThreadFunc;

class SlaveThread : public Noncopyable {
    public:
        explicit SlaveThread(const ThreadFunc&, const std::string& name = "");
    private:
        ThreadFunc _func;
        std::thread::id _thread_id;
        pid_t _tid;
        std::string _name;
        bool _started;
        bool _joined;
};
}
}