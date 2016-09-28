#include "abstract_communicator.h"

// Internal
#include "abstract_link.h"

using namespace domain;

AbstractCommunicator::AbstractCommunicator(VehicleService* vehicleService,
                                           QObject* parent):
    QObject(parent),
    m_vehicleService(vehicleService)
{}

QList<AbstractLink*> AbstractCommunicator::links() const
{
    return m_links;
}

void AbstractCommunicator::addLink(AbstractLink* link)
{
    m_links.append(link);
    link->setParent(this);

    connect(link, &AbstractLink::dataReceived,
            this, &AbstractCommunicator::onDataReceived);

    emit linksChanged(this->links());
}

void AbstractCommunicator::removeLink(AbstractLink* link)
{
    m_links.removeOne(link);
    if (link->parent() == this) link->setParent(nullptr);

    disconnect(link, &AbstractLink::dataReceived,
               this, &AbstractCommunicator::onDataReceived);

    emit linksChanged(this->links());
}
