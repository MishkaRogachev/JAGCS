#include "communicator_worker.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"

#include "abstract_communicator.h"
#include "i_communicator_factory.h"

#include "abstract_link.h"
#include "description_link_factory.h"

using namespace comm;
using namespace domain;

CommunicatorWorker::CommunicatorWorker(QObject* parent):
    QObject(parent)
{}

comm::AbstractCommunicator* CommunicatorWorker::communicator() const
{
    return m_communicator;
}

void CommunicatorWorker::initCommunicator(comm::ICommunicatorFactory* commFactory)
{
    if (m_communicator)
    {
        for (AbstractLink* link: m_descriptedLinks.values())
        {
            m_communicator->removeLink(link);
        }

        disconnect(m_communicator, 0, this, 0);

        delete m_communicator;
    }

    m_communicator = commFactory->create();

    if (m_communicator)
    {
        m_communicator->setParent(this);

        connect(m_communicator, &AbstractCommunicator::linkStatisticsChanged,
                this, &CommunicatorWorker::onLinkStatisticsChanged);
        connect(m_communicator, &AbstractCommunicator::mavLinkStatisticsChanged,
                this, &CommunicatorWorker::onMavLinkStatisticsChanged);
        connect(m_communicator, &AbstractCommunicator::mavLinkProtocolChanged,
                this, &CommunicatorWorker::onMavLinkProtocolChanged);

        for (AbstractLink* link: m_descriptedLinks.values())
        {
            m_communicator->addLink(link);
        }
    }
}

void CommunicatorWorker::updateLinkFromDescription(const dao::LinkDescriptionPtr& description)
{
    DescriptionLinkFactory factory(description);
    AbstractLink* link = nullptr;

    if (m_descriptedLinks.contains(description))
    {
        link = m_descriptedLinks[description];
        factory.update(link);
    }
    else
    {
        link = factory.create();
        if (!link) return;
        link->setParent(this);

        m_descriptedLinks[description] = link;
        if (m_communicator) m_communicator->addLink(link);

        if (description->isAutoConnect()) link->connectLink();
    }
}

void CommunicatorWorker::removeLinkByDescription(const dao::LinkDescriptionPtr& description)
{
    if (m_descriptedLinks.contains(description))
    {
        AbstractLink* link = m_descriptedLinks.take(description);

        if (m_communicator) m_communicator->removeLink(link);
        delete link;
    }
}

void CommunicatorWorker::setLinkConnected(const dao::LinkDescriptionPtr& description, bool connected)
{
    AbstractLink* link = m_descriptedLinks[description];
    if (!link) return;

    link->setConnected(connected);
    emit linkStatisticsChanged(description, 0, 0, link->isConnected());
}

void CommunicatorWorker::onLinkStatisticsChanged(AbstractLink* link, int bytesReceived, int bytesSent)
{
    dao::LinkDescriptionPtr description = m_descriptedLinks.key(link);
    if (description.isNull()) return;

    emit linkStatisticsChanged(description, bytesReceived, bytesSent, link->isConnected());
}

void CommunicatorWorker::onMavLinkStatisticsChanged(AbstractLink* link, int packetsReceived, int packetsDrops)
{
    dao::LinkDescriptionPtr description = m_descriptedLinks.key(link);
    if (description.isNull()) return;

    emit mavLinkStatisticsChanged(description, packetsReceived, packetsDrops);
}

void CommunicatorWorker::onMavLinkProtocolChanged(AbstractLink* link, comm::Protocol protocol)
{
    dao::LinkDescriptionPtr description = m_descriptedLinks.key(link);
    if (description.isNull()) return;

    emit mavLinkProtocolChanged(description, protocol);
}

