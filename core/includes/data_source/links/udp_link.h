#ifndef UDP_LINK_H
#define UDP_LINK_H

// Internal
#include "abstract_link.h"
#include "endpoint.h"

class QUdpSocket;

namespace data_source
{
    class UdpLink: public AbstractLink
    {
        Q_OBJECT

    public:
        UdpLink(quint16 port = 0, QObject* parent = nullptr);

        bool isConnected() const override;

        quint16 port() const;
        dto::EndpointList endpoints() const;
        bool autoResponse() const;

        int count() const;
        dto::Endpoint endpoint(int index) const;

    public slots:
        void connectLink() override;
        void disconnectLink() override;

        void setPort(quint16 port);
        void addEndpoint(const dto::Endpoint& endpoint);
        void removeEndpoint(const dto::Endpoint& endpoint);
        void clearEndpoints();
        void setAutoResponse(bool autoResponse);

    signals:
        void portChanged(int port);
        void endpointsChanged(const dto::EndpointList& endpoints);
        void autoResponseChanged(bool autoResponse);

    protected:
        bool sendDataImpl(const QByteArray& data) override;

    private slots:
        void onReadyRead();

    private:
        QUdpSocket* m_socket;
        quint16 m_port;
        dto::EndpointList m_endpoints;
        bool m_autoResponse;
    };
}

#endif // UDP_LINK_H
