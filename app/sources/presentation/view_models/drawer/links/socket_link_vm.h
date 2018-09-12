#ifndef SOCKET_LINK_VM_H
#define SOCKET_LINK_VM_H

// Internal
#include "link_vm.h"

namespace presentation
{
    class SocketLinkVm: public LinkVm
    {
        Q_OBJECT

        Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

    public:
        explicit SocketLinkVm(QObject* parent = nullptr);

        int port() const;

    public slots:
        void setPort(int port);

    signals:
        void portChanged();
    };
}

#endif // SOCKET_LINK_VM_H
