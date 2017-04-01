#ifndef ABSTRACT_LINK_H
#define ABSTRACT_LINK_H

// Qt
#include <QObject>

namespace data_source
{
    class AbstractLink: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(bool isUp READ isUp NOTIFY upChanged)

        Q_PROPERTY(int bytesReceivedSec READ bytesReceivedSec
                   NOTIFY statisticsChanged)
        Q_PROPERTY(int bytesSentSec READ bytesSentSec
                   NOTIFY statisticsChanged)

        Q_PROPERTY(int packetsReceived READ packetsReceived
                   WRITE setPacketsReceived NOTIFY packetsReceivedChanged)
        Q_PROPERTY(int packetsDrops READ packetsDrops
                   WRITE setPacketsDrops NOTIFY packetsDropsChanged)

    public:
        explicit AbstractLink(QObject* parent = nullptr);

        virtual bool isUp() const = 0;

        int bytesReceivedSec() const;
        int bytesSentSec() const;

        int packetsReceived() const;
        int packetsDrops() const;

    public slots:
        virtual void up() = 0;
        virtual void down() = 0;

        void sendData(const QByteArray& data);

        void setPacketsReceived(int packetsReceived);
        void setPacketsDrops(int packetsDrops);

    signals:
        void upChanged(bool isUp);
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
