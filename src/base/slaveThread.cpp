#include "slaveThread.h"

namespace websocketagent {
namespace base {

SlaveThread::SlaveThread(const ThreadFunc& func, const std::string& name)
    : _started(false),
      _joined(false),
      _thread_id(0),
      _tid(0),
      _func(func),
      _name(name) {
}

}
}