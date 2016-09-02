#ifndef CONNECTION_MANAGER_H
#define CONNECTION_MANAGER_H

// Qt
#include <QObject>
#include <QHostAddress>

namespace domain
{
    class ConnectionManager : public QObject
    {
        Q_OBJECT

    public:
        explicit ConnectionManager(QObject* parent = nullptr);
        ~ConnectionManager() override;

    public slots:
        void addNewSerialLink(const QString& portName, qint32 baudRate);
        void addNewUdpLink(int hostPort, const QHostAddress& address, int port);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // CONNECTION_MANAGER_H
