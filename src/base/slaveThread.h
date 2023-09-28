#pragma once
#include <functional>
#include <thread>
#include <string>
#include "noncopyable.h"

namespace websocketagent {
namespace base {
typedef std::function<void()> ThreadFunc;

class ThreadMetaData : public Noncopyable { 
    public:
        ThreadMetaData(ThreadFunc func, const std::string& name, pid_t pid);

        void runInThread();
    private:
        ThreadFunc _func;
        std::string _name;
        pid_t _pid;

};

class SlaveThread : public Noncopyable {
    public:
        explicit SlaveThread(const ThreadFunc&, const std::string& name = "");

        void start();
    private:
        ThreadFunc _func;
        std::thread::id _thread_id; //线程id
        pid_t _pid; //进程id
        std::string _name;
        bool _started;
        bool _joined;
};
}
}