#ifndef UDP_LINK_H
#define UDP_LINK_H

// Internal
#include "abstract_link.h"
#include "endpoint.h"

class QUdpSocket;

namespace domain
{
    class UdpLink: public AbstractLink
    {
        Q_OBJECT

        Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
        Q_PROPERTY(EndpointList endpoints READ endpoints NOTIFY endpointsChanged)
        Q_PROPERTY(bool autoResponse READ autoResponse WRITE setAutoResponse NOTIFY autoResponseChanged)

    public:
        UdpLink(int port, QObject* parent = nullptr);

        bool isUp() const override;

        int port() const;
        EndpointList endpoints() const;
        bool autoResponse() const;

        Q_INVOKABLE int count() const;
        Q_INVOKABLE Endpoint endpoint(int index) const; // TODO: link and endpoint presenters

    public slots:
        void up() override;
        void down() override;

        void sendDataImpl(const QByteArray& data) override;

        void setPort(int port);
        void addEndpoint(const Endpoint& endpoint);
        void removeEndpoint(const Endpoint& endpoint);
        void setAutoResponse(bool autoResponse);

    signals:
        void portChanged(int port);
        void endpointsChanged(const EndpointList& endpoints);
        void autoResponseChanged(bool autoResponse);

    private slots:
        void readPendingDatagrams();

    private:
        QUdpSocket* m_socket;
        int m_port;
        EndpointList m_endpoints;
        bool m_autoResponse;
    };
}

#endif // UDP_LINK_H
