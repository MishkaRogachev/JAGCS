#ifndef UDP_LINK_H
#define UDP_LINK_H

#include "abstract_link.h"

class QUdpSocket;

namespace domain
{
    class UdpLink: public AbstractLink
    {
        Q_OBJECT

        Q_PROPERTY(int rxPort READ rxPort WRITE setRxPort NOTIFY rxPortChanged)
        Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
        Q_PROPERTY(int txPort READ txPort WRITE setTxPort NOTIFY txPortChanged)

    public:
        UdpLink(int rxPort, const QString& address, int txPort,
                QObject* parent = nullptr);

        bool isUp() const override;

        int rxPort() const;
        QString address() const;
        int txPort() const;

    public slots:
        void up() override;
        void down() override;

        void sendData(const QByteArray& data) override;

        void setRxPort(int port);
        void setAddress(const QString& address);
        void setTxPort(int port);

    signals:
        void rxPortChanged(int port);
        void addressChanged(QString address);
        void txPortChanged(int port);

    private slots:
        void readPendingDatagrams();

    private:
        QUdpSocket* m_socket;
        int m_rxPort;
        QString m_address;
        int m_txPort;
    };
}

#endif // UDP_LINK_H
