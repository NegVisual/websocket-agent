#include "noncopyable.h"
#include <iostream>

namespace websocketagent {
namespace base {

template<typename T>
class Singleton : public Noncopyable {
    public:
        static T& getInstance() {
            static T instance;
            return instance;
        }
};
}
}