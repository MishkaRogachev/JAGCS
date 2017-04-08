#include "description_link_factory.h"

// Internal
#include "link_description.h"

#include "udp_link.h"
#include "serial_link.h"

using namespace data_source;

DescriptionLinkFactory::DescriptionLinkFactory(
        const LinkDescriptionPtr& description):
    ILinkFactory(),
    m_description(description)
{}

AbstractLink* DescriptionLinkFactory::create()
{
    if (m_description.isNull()) return nullptr;

    switch (m_description->type())
    {
    case LinkDescription::Udp:
        return new UdpLink(m_description->port());
    case LinkDescription::Serial:
        return new SerialLink(m_description->device(), m_description->baudRate());
    default:
        return nullptr;
    }
}

void DescriptionLinkFactory::update(AbstractLink* link)
{
    if (m_description.isNull()) return;

    switch (m_description->type())
    {
    case LinkDescription::Udp:
    {
       UdpLink* udpLink = qobject_cast<UdpLink*>(link);
       if (!udpLink) return;

       udpLink->setPort(m_description->port());

       break;
    }
    case LinkDescription::Serial:
    {
        SerialLink* serialLink = qobject_cast<SerialLink*>(link);
        if (!serialLink) return;

        serialLink->setDevice(m_description->device());
        serialLink->setBaudRate(m_description->baudRate());

        break;
    }
    default:
        break;
    }
}

LinkDescriptionPtr DescriptionLinkFactory::description() const
{
    return m_description;
}

void DescriptionLinkFactory::setDescription(const LinkDescriptionPtr& description)
{
    m_description = description;
}
