#ifndef UDP_LINK_VM_H
#define UDP_LINK_VM_H

// Internal
#include "socket_link_vm.h"

namespace presentation
{
    class UdpLinkVm: public SocketLinkVm
    {
        Q_OBJECT

        Q_PROPERTY(QStringList endpoints READ endpoints WRITE setEndpoints NOTIFY endpointsChanged)
        Q_PROPERTY(bool autoAdd READ autoAdd WRITE setAutoAdd NOTIFY autoAddChanged)

    public:
        explicit UdpLinkVm(QObject* parent = nullptr);

        QStringList endpoints() const;
        bool autoAdd() const;

    public slots:
        void setEndpoints(const QStringList& endpoints);

        void setAutoAdd(bool autoAdd);

    signals:
        void endpointsChanged();
        void autoAddChanged();
    };
}

#endif // UDP_LINK_VM_H
