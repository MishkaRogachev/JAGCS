#include "abstract_communicator.h"

// Internal
#include "abstract_link.h"

using namespace domain;

AbstractCommunicator::AbstractCommunicator(VehicleService* vehicleService,
                                           QObject* parent):
    QObject(parent),
    m_vehicleService(vehicleService),
    m_addLinkEnabled(true)
{}

bool AbstractCommunicator::isAddLinkEnabled() const
{
    return m_addLinkEnabled;
}

QList<AbstractLink*> AbstractCommunicator::links() const
{
    return m_links;
}

void AbstractCommunicator::setAddLinkEnabled(bool addLinkEnabled)
{
    if (m_addLinkEnabled == addLinkEnabled) return;

    m_addLinkEnabled = addLinkEnabled;
    emit addLinkEnabledChanged(addLinkEnabled);
}

void AbstractCommunicator::sendDataAllLinks(const QByteArray& data)
{
    for (AbstractLink* link: m_links)
    {
        if (link->isUp()) link->sendData(data);
    }
}

void AbstractCommunicator::addLink(AbstractLink* link)
{
    m_links.append(link);
    link->setParent(this);

    connect(link, &AbstractLink::dataReceived,
            this, &AbstractCommunicator::onDataReceived);

    emit linksChanged();
}

void AbstractCommunicator::removeLink(AbstractLink* link)
{
    m_links.removeOne(link);
    if (link->parent() == this) link->setParent(nullptr);

    disconnect(link, &AbstractLink::dataReceived,
               this, &AbstractCommunicator::onDataReceived);

    emit linksChanged();
}
