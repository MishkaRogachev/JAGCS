#ifndef TCP_LINK_VM_H
#define TCP_LINK_VM_H

// Internal
#include "socket_link_vm.h"

namespace presentation
{
    class TcpLinkVm: public SocketLinkVm
    {
        Q_OBJECT

    public:
        explicit TcpLinkVm(QObject* parent = nullptr);
    };
}

#endif // TCP_LINK_VM_H
