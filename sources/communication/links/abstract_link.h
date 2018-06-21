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

        int takeBytesReceived();
        int takeBytesSent();

    public slots:
        void setConnected(bool connected);
        virtual void connectLink() = 0;
        virtual void disconnectLink() = 0;

        void sendData(const QByteArray& data);

    signals:
        void connectedChanged(bool connected);
        void errored(QString error);
        void dataReceived(QByteArray data);
        void dataSent();

    protected:
        virtual bool sendDataImpl(const QByteArray& data) = 0;

    protected slots:
        void receiveData(const QByteArray& data);

    public slots: // QOverload require public
        void onSocketError(int error);

    private:
        int m_bytesReceived = 0;
        int m_bytesSent = 0;
    };
}

#endif // ABSTRACT_LINK_H
