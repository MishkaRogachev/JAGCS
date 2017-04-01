#include "description_link_factory.h"

// Internal
#include "link_description.h"

#include "udp_link.h"
#include "serial_link.h"

using namespace data_source;

DescriptionLinkFactory::DescriptionLinkFactory():
    ILinkFactory()
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

LinkDescriptionPtr DescriptionLinkFactory::description() const
{
    return m_description;
}

void DescriptionLinkFactory::setDescription(const LinkDescriptionPtr& description)
{
    m_description = description;
}
