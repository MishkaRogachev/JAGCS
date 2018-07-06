#include "mock_link.h"

// Qt
#include <QDebug>

using namespace data_source;

MockLink::MockLink(QObject* parent):
    AbstractLink(parent)
{}

bool MockLink::isConnected() const
{
    return true;
}

bool MockLink::waitData(int timeout)
{
    Q_UNUSED(timeout)

    return true;
}

QList<MockLink*> MockLink::links() const
{
    return m_links;
}

void MockLink::connectLink()
{}

void MockLink::disconnectLink()
{}

void MockLink::addLink(MockLink* link)
{
    if (m_links.contains(link)) return;

    m_links.append(link);
    link->addLink(this);

    emit linkAdded(link);
}

void MockLink::removeLink(MockLink* link)
{
    if (m_links.removeOne(link)) emit linkAdded(link);
}

bool MockLink::sendDataImpl(const QByteArray& data)
{
    bool ok = false;
    for (MockLink* link: m_links)
    {
        link->receiveData(data);
        ok = true;
    }

    return ok;
}
