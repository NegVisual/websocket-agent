#include "noncopyable.h"
#include <iostream>
#include <memory>
#include <mutex>

namespace websocketagent {
namespace base {

// template<typename T>
// class Singleton : public Noncopyable {
//     public:
//         static std::shared_ptr<T> getInstance() {
//         if (instance.get() == nullptr) {
//             std::lock_guard<std::mutex> lock(mutex);
//             if (instance.get() == nullptr) {
//                 instance = std::make_shared<T>();
//             }
//         }
//         return instance;
//     }

//     static std::shared_ptr<T> instance;
//     static std::mutex mutex;
// };

// template<typename T>
// std::shared_ptr<T> Singleton<T>::instance = nullptr;

// template<typename T>
// std::mutex Singleton<T>::mutex;

template<typename T>
class Singleton : public Noncopyable {
    public:
        static std::shared_ptr<T> getInstance() {
            static std::shared_ptr<T> instance = std::make_shared<T>();
            return instance;
        }
};
}
}