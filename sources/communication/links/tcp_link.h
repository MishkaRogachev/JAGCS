#ifndef TCP_LINK_H
#define TCP_LINK_H

// Internal
#include "abstract_link.h"
#include "endpoint.h"

class QTcpSocket;

namespace comm
{
    class TcpLink: public AbstractLink
    {
        Q_OBJECT

    public:
        TcpLink(const Endpoint& endpoint = Endpoint(), QObject* parent = nullptr);

        bool isConnected() const override;

        Endpoint endpoint() const;

        int count() const;
        Endpoint endpoint(int index) const;

    public slots:
        void connectLink() override;
        void disconnectLink() override;

        void setEndpoint(const Endpoint& endpoint);

    signals:
        void endpointChanged(const Endpoint& endpoint);

    protected:
        bool sendDataImpl(const QByteArray& data) override;

    private slots:
        void onReadyRead();

    private:
        QTcpSocket* m_socket;
        Endpoint m_endpoint;
    };
}

#endif // TCP_LINK_H
