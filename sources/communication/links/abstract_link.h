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
        void upChanged(bool isConnected);
        void dataReceived(const QByteArray& data);

    protected:
        virtual void sendDataImpl(const QByteArray& data) = 0;

    protected slots:
        void receiveData(const QByteArray& data);

    private:
        int m_bytesReceived = 0;
        int m_bytesSent = 0;
    };
}

#endif // ABSTRACT_LINK_H
