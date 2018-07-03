#ifndef ENDPOINT_H
#define ENDPOINT_H

// Qt
#include <QObject>
#include <QHostAddress>

namespace comm
{
    class Endpoint
    {
        Q_GADGET

        Q_PROPERTY(QHostAddress address READ address CONSTANT)
        Q_PROPERTY(quint16 port READ port CONSTANT)

    public:
        Endpoint(const QHostAddress& address = QHostAddress(), quint16 port = 0);

        QHostAddress address() const;
        void setAddress(const QHostAddress& address);

        quint16 port() const;
        void setPort(quint16 port);

        bool isValid() const;

        bool operator ==(const Endpoint& other);

    private:
        QHostAddress m_address;
        quint16 m_port;
    };

    using EndpointList = QList<Endpoint>;
}

#endif // ENDPOINT_H
