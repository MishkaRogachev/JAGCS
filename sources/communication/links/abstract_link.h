#ifndef ABSTRACT_LINK_H
#define ABSTRACT_LINK_H

// Qt
#include <QObject>

namespace comm
{
    class AbstractLink: public QObject
    {
        Q_OBJECT

    public:
        enum Protocol
        {
            UnknownProtocol,
            Mavlink1,
            Mavlink2
        };

        explicit AbstractLink(QObject* parent = nullptr);

        virtual bool isConnected() const = 0;

        int bytesReceivedSec() const;
        int bytesSentSec() const;

        int packetsReceived() const;
        int packetsDrops() const;

        Protocol protocol() const;

    public slots:
        void setConnected(bool connected);
        virtual void connectLink();
        virtual void disconnectLink();

        void sendData(const QByteArray& data);

        void setPacketsReceived(int packetsReceived);
        void setPacketsDrops(int packetsDrops);

        void setProtocol(Protocol protocol);

    signals:
        void upChanged(bool isConnected);
        void dataReceived(const QByteArray& data);

        void statisticsChanged();

        void packetsReceivedChanged(int packetsReceived);
        void packetsDropsChanged(int packetsDrops);

        void protocolChanged(Protocol protocol);

    protected:
        virtual void sendDataImpl(const QByteArray& data) = 0;

        void timerEvent(QTimerEvent* event);

    protected slots:
        void receiveData(const QByteArray& data);

    private:
        int m_bytesReceivedSec = 0;
        int m_bytesReceived = 0;
        int m_bytesSentSec = 0;
        int m_bytesSent = 0;
        int m_packetsReceived = 0;
        int m_packetsDrops = 0;
        int m_statisticsTimer = 0;

        Protocol m_protocol = UnknownProtocol;
        Q_ENUM(Protocol)
    };
}

#endif // ABSTRACT_LINK_H
