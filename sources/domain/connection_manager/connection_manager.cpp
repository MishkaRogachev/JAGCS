#include "connection_manager.h"

// Internal
#include "mavlink_communicator.h"
#include "serial_link.h"
#include "udp_link.h"

using namespace domain;

class ConnectionManager::Impl
{
public:
    QList<AbstractLink*> links;
};

ConnectionManager::ConnectionManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

ConnectionManager::~ConnectionManager()
{
    delete d;
}

QList<AbstractLink*> ConnectionManager::links() const
{
    return d->links;
}

void ConnectionManager::addNewSerialLink(const QString& portName, qint32 baudRate)
{
    auto link = new SerialLink(portName, baudRate);
    link->setObjectName(tr("Serial"));

    d->links.append(link);
    emit linksChanged(this->links());
}

void ConnectionManager::addNewUdpLink(int hostPort, const QString& address,
                                      int port)
{
    auto link = new UdpLink(hostPort, address, port);
    link->setObjectName(tr("UDP"));

    d->links.append(link);
    emit linksChanged(this->links());
}

void ConnectionManager::removeLink(AbstractLink* link)
{
    d->links.removeOne(link);
    emit linksChanged(this->links());
}
