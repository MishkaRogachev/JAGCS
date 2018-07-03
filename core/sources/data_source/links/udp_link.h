#ifndef UDP_LINK_H
#define UDP_LINK_H

// Internal
#include "abstract_link.h"
#include "endpoint.h"

class QUdpSocket;

namespace comm
{
    class UdpLink: public AbstractLink
    {
        Q_OBJECT

    public:
        UdpLink(quint16 port = 0, QObject* parent = nullptr);

        bool isConnected() const override;

        quint16 port() const;
        EndpointList endpoints() const;
        bool autoResponse() const;

        int count() const;
        Endpoint endpoint(int index) const;

    public slots:
        void connectLink() override;
        void disconnectLink() override;

        void setPort(quint16 port);
        void addEndpoint(const Endpoint& endpoint);
        void removeEndpoint(const Endpoint& endpoint);
        void clearEndpoints();
        void setAutoResponse(bool autoResponse);

    signals:
        void portChanged(int port);
        void endpointsChanged(const EndpointList& endpoints);
        void autoResponseChanged(bool autoResponse);

    protected:
        bool sendDataImpl(const QByteArray& data) override;

    private slots:
        void onReadyRead();

    private:
        QUdpSocket* m_socket;
        quint16 m_port;
        EndpointList m_endpoints;
        bool m_autoResponse;
    };
}

#endif // UDP_LINK_H
