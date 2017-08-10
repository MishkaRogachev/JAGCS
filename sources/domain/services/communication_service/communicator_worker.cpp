#include "communicator_worker.h"

// Qt
#include <QDebug>

// Internal
#include "link_description.h"

#include "abstract_communicator.h"

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

void CommunicatorWorker::setCommunicator(comm::AbstractCommunicator* value)
{
    if (m_communicator)
    {
        for (AbstractLink* link: m_descriptedLinks.values())
        {
            m_communicator->removeLink(link);
        }
    }
    m_communicator = value;

    for (AbstractLink* link: m_descriptedLinks.values())
    {
        m_communicator->addLink(link);
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

        m_descriptedLinks[description] = link;
        if (m_communicator) m_communicator->addLink(link);

        if (description->isAutoConnect()) link->connectLink();

        link->setParent(this);
        connect(link, &AbstractLink::statisticsChanged,
                this, &CommunicatorWorker::onLinkStatisticsChanged);
    }

    emit link->statisticsChanged();
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
    link->statisticsChanged();
}

void CommunicatorWorker::onLinkStatisticsChanged()
{
    AbstractLink* link = qobject_cast<AbstractLink*>(this->sender());
    dao::LinkDescriptionPtr description = m_descriptedLinks.key(link);
    if (description.isNull()) return;

    emit linkStatisticsChanged(description,
                               link->bytesReceivedSec(),
                               link->bytesSentSec(),
                               link->isConnected());
}

