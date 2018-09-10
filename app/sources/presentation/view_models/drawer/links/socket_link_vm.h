#ifndef SOCKET_LINK_VM_H
#define SOCKET_LINK_VM_H

// Internal
#include "link_vm.h"

namespace presentation
{
    class SocketLinkVm: public LinkVm
    {
        Q_OBJECT

    public:
        explicit SocketLinkVm(QObject* parent = nullptr);
    };
}

#endif // SOCKET_LINK_VM_H
