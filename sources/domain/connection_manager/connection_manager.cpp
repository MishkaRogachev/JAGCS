#include "connection_manager.h"

// Internal
#include "mavlink_communicator.h"
#include "serial_link.h"
#include "udp_link.h"

using namespace domain;

class ConnectionManager::Impl
{
public:
    data_source::mavlink::Communicator* communicator;
};

ConnectionManager::ConnectionManager(QObject* parent):
    QObject(parent),
    d(new Impl())
{
    d->communicator = new data_source::mavlink::Communicator(this);
}

ConnectionManager::~ConnectionManager()
{
    delete d;
}

QList<data_source::ILink*> ConnectionManager::links() const
{
    QList<data_source::ILink*> links;

    for (const auto& link: d->communicator->links())
        links.append(link);

    return links;
}

void ConnectionManager::addNewSerialLink(const QString& portName, qint32 baudRate)
{
    auto link = new data_source::SerialLink(portName, baudRate);
    link->setObjectName(tr("Serial"));

    d->communicator->addLink(link);
    emit linksChanged(this->links());
}

void ConnectionManager::addNewUdpLink(int hostPort, const QString& address,
                                      int port)
{
    auto link = new data_source::UdpLink(hostPort, address, port);
    link->setObjectName(tr("UDP"));

    d->communicator->addLink(link);
    emit linksChanged(this->links());
}

void ConnectionManager::removeLink(data_source::ILink* link)
{
    d->communicator->removeLink(link);
    emit linksChanged(this->links());
}
