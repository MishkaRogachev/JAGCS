#include "connection_manager.h"

// Internal
#include "mavlink_communicator.h"
#include "mavlink_serial_link.h"
#include "mavlink_udp_link.h"

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
    d->communicator->addLink(
                new data_source::mavlink::SerialLink(portName, baudRate));
}

void ConnectionManager::addNewUdpLink(int hostPort, const QHostAddress& address,
                                      int port)
{
    d->communicator->addLink(
                new data_source::mavlink::UdpLink(hostPort, address, port));
}
