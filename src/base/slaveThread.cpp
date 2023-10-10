#include "slaveThread.h"
#include <iostream>
#include <thread>
#include <unistd.h> // 用于获取进程ID

namespace websocketagent {
namespace reactor {
SlaveThread::SlaveThread(const ThreadFunc& func, const int thread_index)
    : _started(false), _joined(false), _thread_id(0),
      _pid(0), _func(func), _thread_index(thread_index) {
}

void SlaveThread::start() {
  _thread = std::thread(&SlaveThread::runInThread, this);
  // t.join();
}

void SlaveThread::runInThread() {
  // 获取当前线程的ID
  _thread_id = std::this_thread::get_id();

  // 获取当前进程的ID
  _pid = getpid();

  std::cout << "SlaveThread::start! thread_index: " <<  _thread_index 
            << ", threadId: " << _thread_id 
            << ", processId:" << _pid << std::endl; 
  _func();
}

void SlaveThread::setReactor(std::shared_ptr<SlaveFDReactor> reactor) {
  _reactor = reactor;
}

SlaveThread::~SlaveThread() {
  if(_thread.joinable()) {
    _thread.join();
  }
}

}
}