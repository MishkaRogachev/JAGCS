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
        Q_PROPERTY(QList<Endpoint> endpoints READ endpoints NOTIFY endpointsChanged)
        Q_PROPERTY(bool autoResponse READ autoResponse WRITE setAutoResponse NOTIFY autoResponseChanged)

    public:
        UdpLink(int port, QObject* parent = nullptr);

        bool isUp() const override;

        int port() const;
        QList<Endpoint> endpoints() const;
        bool autoResponse() const;

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
        void endpointsChanged(const QList<Endpoint>& endpoints);
        void autoResponseChanged(bool autoResponse);

    private slots:
        void readPendingDatagrams();

    private:
        QUdpSocket* m_socket;
        int m_port;
        QList<Endpoint> m_endpoints;
        bool m_autoResponse;
    };
}

#endif // UDP_LINK_H
