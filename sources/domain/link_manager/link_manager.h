#ifndef LINK_MANAGER_H
#define LINK_MANAGER_H

// Qt
#include <QObject>
#include <QHostAddress>

// Internal
#include "abstract_link.h"

namespace domain
{
    class LinkManager: public QObject
    {
        Q_OBJECT

    public:
        explicit LinkManager(QObject* parent = nullptr);
        ~LinkManager() override;

        QList<AbstractLink*> links() const;

    public slots:
        void addNewSerialLink(const QString& portName, qint32 baudRate);
        void addNewUdpLink(int hostPort, const QString& address, int port);

        void removeLink(AbstractLink* link);

    signals:
        void linksChanged(QList<AbstractLink*>);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // LINK_MANAGER_H
