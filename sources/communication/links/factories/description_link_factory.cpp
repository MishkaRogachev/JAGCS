#include "description_link_factory.h"

// Internal
#include "link_description.h"

#include "udp_link.h"
#include "serial_link.h"

using namespace dao;
using namespace comm;

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
        return new UdpLink(m_description->parameter(dao::LinkDescription::Port).toInt());
    case LinkDescription::Serial:
        return new SerialLink(m_description->parameter(dao::LinkDescription::Device).toString(),
                              m_description->parameter(dao::LinkDescription::BaudRate).toInt());
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

       udpLink->setPort(m_description->parameter(dao::LinkDescription::Port).toInt());

       break;
    }
    case LinkDescription::Serial:
    {
        SerialLink* serialLink = qobject_cast<SerialLink*>(link);
        if (!serialLink) return;

        serialLink->setDevice(m_description->parameter(dao::LinkDescription::Device).toString());
        serialLink->setBaudRate(m_description->parameter(dao::LinkDescription::BaudRate).toInt());

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
