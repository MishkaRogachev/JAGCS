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
        explicit AbstractLink(QObject* parent = nullptr);

        virtual bool isConnected() const = 0;

        int bytesReceivedSec() const;
        int bytesSentSec() const;

        int packetsReceived() const;
        int packetsDrops() const;

    public slots:
        void setConnected(bool connected);
        virtual void connectLink();
        virtual void disconnectLink();

        void sendData(const QByteArray& data);

        void setPacketsReceived(int packetsReceived);
        void setPacketsDrops(int packetsDrops);

    signals:
        void upChanged(bool isConnected);
        void dataReceived(const QByteArray& data);

        void statisticsChanged();

        void packetsReceivedChanged(int packetsReceived);
        void packetsDropsChanged(int packetsDrops);

    protected:
        virtual void sendDataImpl(const QByteArray& data) = 0;

        void timerEvent(QTimerEvent* event);

    protected slots:
        void receiveData(const QByteArray& data);

    private:
        int m_bytesReceivedSec;
        int m_bytesReceived;
        int m_bytesSentSec;
        int m_bytesSent;
        int m_packetsReceived;
        int m_packetsDrops;
        int m_statisticsTimer;
    };
}

#endif // ABSTRACT_LINK_H
