#include "communicator_worker.h"

// Qt
#include <QTime>
#include <QDebug>

// Internal
#include "link_description.h"

#include "abstract_communicator.h"
#include "i_communicator_factory.h"

#include "abstract_link.h"
#include "description_link_factory.h"

namespace
{
    dao::LinkDescription::Protocol toDaoProtocol(comm::AbstractCommunicator::Protocol protocol)
    {
        switch (protocol) {
        case comm::AbstractCommunicator::MavLink1: return dao::LinkDescription::MavLink1;
        case comm::AbstractCommunicator::MavLink2: return dao::LinkDescription::MavLink2;
        default:
        case comm::AbstractCommunicator::Unknown: return dao::LinkDescription::UnknownProtocol;
        }
    }
}

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

void CommunicatorWorker::updateLinkFromDescription(
        const dao::LinkDescriptionPtr& description)
{
    DescriptionLinkFactory factory(description);
    AbstractLink* link = nullptr;

    if (m_descriptedLinks.contains(description->id()))
    {
        link = m_descriptedLinks[description->id()];
        factory.update(link);
    }
    else
    {
        link = factory.create();
        if (!link) return;
        link->setParent(this);

        m_descriptedLinks[description->id()] = link;
        if (m_communicator) m_communicator->addLink(link);

        if (description->isAutoConnect()) link->connectLink();
    }
}

void CommunicatorWorker::removeLinkByDescription(
        const dao::LinkDescriptionPtr& description)
{
    if (m_descriptedLinks.contains(description->id()))
    {
        AbstractLink* link = m_descriptedLinks.take(description->id());

        if (m_communicator) m_communicator->removeLink(link);
        delete link;
    }
}

void CommunicatorWorker::setLinkConnected(const dao::LinkDescriptionPtr& description,
                                          bool connected)
{
    AbstractLink* link = m_descriptedLinks[description->id()];
    if (!link) return;

    link->setConnected(connected);
    emit linkStatusChanged(description->id(), link->isConnected());
}

void CommunicatorWorker::onLinkStatisticsChanged(AbstractLink* link,
                                                 int bytesReceived,
                                                 int bytesSent)
{
    int linkId = m_descriptedLinks.key(link, 0);
    if (!linkId) return;

    emit linkStatisticsChanged(linkId,
                               QTime::currentTime().msecsSinceStartOfDay(),
                               bytesReceived, bytesSent);
}

void CommunicatorWorker::onMavLinkStatisticsChanged(AbstractLink* link,
                                                    int packetsReceived,
                                                    int packetsDrops)
{
    int linkId = m_descriptedLinks.key(link, 0);
    if (!linkId) return;

    emit mavLinkStatisticsChanged(linkId, packetsReceived, packetsDrops);
}

void CommunicatorWorker::onMavLinkProtocolChanged(AbstractLink* link,
                                                  AbstractCommunicator::Protocol protocol)
{
    int linkId = m_descriptedLinks.key(link, 0);
    if (!linkId) return;

    emit mavLinkProtocolChanged(linkId, ::toDaoProtocol(protocol));
}

