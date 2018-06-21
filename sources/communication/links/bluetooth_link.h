#ifndef BLUETOOTH_LINK_H
#define BLUETOOTH_LINK_H

#include "abstract_link.h"

class QBluetoothSocket;

namespace comm
{
    class BluetoothLink: public AbstractLink
    {
        Q_OBJECT

    public:
        explicit BluetoothLink(const QString& address = QString(), QObject* parent = nullptr);

        bool isConnected() const override;

        QString address() const;

    public slots:
        void connectLink() override;
        void disconnectLink() override;

        void setAddress(const QString& address);

    signals:
        void addressChanged(QString address);

    protected:
        bool sendDataImpl(const QByteArray& data) override;

    private slots:
        void onReadyRead();
        void onError(int error);

    private:
        QString m_address;
        QBluetoothSocket* m_socket = nullptr;
    };
}

#endif // BLUETOOTH_LINK_H
