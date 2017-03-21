#include "abstract_communicator.h"

// Internal
#include "abstract_link.h"

using namespace data_source;

AbstractCommunicator::AbstractCommunicator(QObject* parent):
    QObject(parent)
{}

QList<AbstractLink*> AbstractCommunicator::links() const
{
    return m_links;
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
