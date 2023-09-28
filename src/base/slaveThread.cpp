#include "slaveThread.h"
#include <iostream>

namespace websocketagent {
namespace base {

ThreadMetaData::ThreadMetaData(ThreadFunc func, const std::string& name, pid_t pid) 
  : _func(std::move(func)), _name(name), _pid(pid){

}

void ThreadMetaData::runInThread() {
  
}

SlaveThread::SlaveThread(const ThreadFunc& func, const std::string& name)
    : _started(false),
      _joined(false),
      _thread_id(0),
      _pid(0),
      _func(func),
      _name(name) {
}


void SlaveThread::start() {
  std::cout << "SlaveThread::start" << std::endl; 
}

}
}