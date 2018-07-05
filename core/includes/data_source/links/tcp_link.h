#ifndef TCP_LINK_H
#define TCP_LINK_H

// Internal
#include "abstract_link.h"
#include "endpoint.h"

class QTcpSocket;

namespace data_source
{
    class TcpLink: public AbstractLink
    {
        Q_OBJECT

    public:
        TcpLink(const dto::Endpoint& endpoint = dto::Endpoint(), QObject* parent = nullptr);

        bool isConnected() const override;

        dto::Endpoint endpoint() const;

        int count() const;
        dto::Endpoint endpoint(int index) const;

    public slots:
        void connectLink() override;
        void disconnectLink() override;

        void setEndpoint(const dto::Endpoint& endpoint);

    signals:
        void endpointChanged(const dto::Endpoint& endpoint);

    protected:
        bool sendDataImpl(const QByteArray& data) override;

    private slots:
        void onReadyRead();

    private:
        QTcpSocket* m_socket;
        dto::Endpoint m_endpoint;
    };
}

#endif // TCP_LINK_H
