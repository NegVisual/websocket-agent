#include "noncopyable.h"
#include "channel.h"

namespace websocketagent {
namespace reactor {
class Acceptor : websocketagent::base::Noncopyable
{
    public:
        Acceptor(int port, bool reuseport);
        ~Acceptor();

        void listen();

        bool listening() const { return listening_; }

        // Deprecated, use the correct spelling one above.
        // Leave the wrong spelling here in case one needs to grep it for error messages.
        // bool listenning() const { return listening(); }

    private:
        Channel acceptChannel_;

        bool listening_;
        int idleFd_;
        int idleFd_;
};
}
}