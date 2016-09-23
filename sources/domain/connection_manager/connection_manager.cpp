#include "connection_manager.h"

// Internal
#include "mavlink_communicator.h"
#include "serial_link.h"
#include "udp_link.h"

using namespace domain;

class ConnectionManager::Impl
{
public:
    QList<data_source::AbstractLink*> links;
};

ConnectionManager::ConnectionManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{}

ConnectionManager::~ConnectionManager()
{
    delete d;
}

QList<data_source::AbstractLink*> ConnectionManager::links() const
{
    return d->links;
}

void ConnectionManager::addNewSerialLink(const QString& portName, qint32 baudRate)
{
    auto link = new data_source::SerialLink(portName, baudRate);
    link->setObjectName(tr("Serial"));

    d->links.append(link);
    emit linksChanged(this->links());
}

void ConnectionManager::addNewUdpLink(int hostPort, const QString& address,
                                      int port)
{
    auto link = new data_source::UdpLink(hostPort, address, port);
    link->setObjectName(tr("UDP"));

    d->links.append(link);
    emit linksChanged(this->links());
}

void ConnectionManager::removeLink(data_source::AbstractLink* link)
{
    d->links.removeOne(link);
    emit linksChanged(this->links());
}
