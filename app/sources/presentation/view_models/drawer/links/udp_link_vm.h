#ifndef UDP_LINK_VM_H
#define UDP_LINK_VM_H

// Internal
#include "socket_link_vm.h"

namespace presentation
{
    class UdpLinkVm: public SocketLinkVm
    {
        Q_OBJECT

    public:
        explicit UdpLinkVm(QObject* parent = nullptr);
    };
}

#endif // UDP_LINK_VM_H
