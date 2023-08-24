#pragma once

namespace websocketagent {
namespace base
{

    class Noncopyable
    {
        public:
        Noncopyable(const Noncopyable&) = delete;
        void operator=(const Noncopyable&) = delete;

        protected:
        Noncopyable() = default;
        ~Noncopyable() = default;
    };

}  // namespace base
}  // websocketagent
