#include "slaveThread.h"
#include <iostream>
#include <thread>

namespace websocketagent {
namespace reactor {
SlaveThread::SlaveThread(const ThreadFunc& func, const std::string& name)
    : _started(false), _joined(false), _thread_id(0),
      _pid(0), _func(func), _name(name) {
}

void SlaveThread::start() {
  std::cout << "SlaveThread::start" << std::endl; 
  _thread = std::thread(&SlaveThread::runInThread, this);
  // t.join();
}

void SlaveThread::runInThread() {

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