#ifndef TCP_LINK_VM_H
#define TCP_LINK_VM_H

// Internal
#include "socket_link_vm.h"

namespace presentation
{
    class TcpLinkVm: public SocketLinkVm
    {
        Q_OBJECT

        Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)

    public:
        explicit TcpLinkVm(QObject* parent = nullptr);

        QString address() const;

    public slots:
        void setAddress(const QString& address);

    signals:
        void addressChanged();

    protected:
        void changed() override;
    };
}

#endif // TCP_LINK_VM_H
