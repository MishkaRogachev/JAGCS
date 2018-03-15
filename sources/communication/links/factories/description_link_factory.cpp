#include "description_link_factory.h"

// Internal
#include "link_description.h"

#include "udp_link.h"
#include "serial_link.h"

using namespace dto;
using namespace comm;

namespace
{
    UdpLink* updateUdpLink(UdpLink* udpLink, const LinkDescriptionPtr& description)
    {
        udpLink->setPort(description->parameter(dto::LinkDescription::Port).toInt());

        udpLink->setAutoResponse(
                    description->parameter(dto::LinkDescription::UdpAutoResponse).toBool());

        udpLink->clearEndpoints();
        QString endpoints = description->parameter(dto::LinkDescription::Endpoints).toString();
        if (!endpoints.isEmpty())
        {
            for (const QString& endpoint: endpoints.split(","))
            {
                QStringList split = endpoint.split("/");
                QHostAddress address = split.count() > 0 ? QHostAddress(split.first()) :
                                                           QHostAddress();
                qDebug() << split;
                quint16 port =split.count() > 1 ? split.at(1).toUInt() : 0;
                udpLink->addEndpoint(Endpoint(address, port));
            }
        }

        return udpLink;
    }
}

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
    case LinkDescription::Udp:{
        return ::updateUdpLink(new UdpLink(), m_description);
    }
    case LinkDescription::Serial:
        return new SerialLink(m_description->parameter(dto::LinkDescription::Device).toString(),
                              m_description->parameter(dto::LinkDescription::BaudRate).toInt());
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
       if (udpLink) ::updateUdpLink(udpLink, m_description);

       break;
    }
    case LinkDescription::Serial:
    {
        SerialLink* serialLink = qobject_cast<SerialLink*>(link);
        if (!serialLink) return;

        serialLink->setDevice(m_description->parameter(dto::LinkDescription::Device).toString());
        serialLink->setBaudRate(m_description->parameter(dto::LinkDescription::BaudRate).toInt());

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
