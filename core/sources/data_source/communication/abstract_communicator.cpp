#include "abstract_communicator.h"

// Qt
#include <QDebug>

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
        if (link->isConnected()) link->sendData(data);
    }
}

void AbstractCommunicator::addLink(AbstractLink* link)
{
    m_links.append(link);

    connect(link, &AbstractLink::dataReceived, this, &AbstractCommunicator::onDataReceived);
    emit linkAdded(link);
}

void AbstractCommunicator::removeLink(AbstractLink* link)
{
    if (!m_links.removeOne(link)) return;

    disconnect(link, &AbstractLink::dataReceived, this, &AbstractCommunicator::onDataReceived);
    emit linkRemoved(link);
}
