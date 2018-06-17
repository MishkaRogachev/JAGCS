#include "description_link_factory.h"

// Internal
#include "link_description.h"

#include "serial_link.h"
#include "udp_link.h"
#include "tcp_link.h"

using namespace dto;
using namespace comm;

namespace
{
    SerialLink* updateSerialLink(SerialLink* serialLink, const LinkDescriptionPtr& description)
    {
        serialLink->setDevice(description->parameter(dto::LinkDescription::Device).toString());
        serialLink->setBaudRate(description->parameter(dto::LinkDescription::BaudRate).toInt());

        return serialLink;
    }

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
                quint16 port =split.count() > 1 ? split.at(1).toUInt() : 0;
                udpLink->addEndpoint(Endpoint(address, port));
            }
        }

        return udpLink;
    }

    TcpLink* updateTcpLink(TcpLink* tcpLink, const LinkDescriptionPtr& description)
    {
        Endpoint endpoint;

        endpoint.setAddress(QHostAddress(description->parameter(LinkDescription::Address).toString()));
        endpoint.setPort(description->parameter(dto::LinkDescription::Port).toInt());

        tcpLink->setEndpoint(endpoint);

        return tcpLink;
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
    case LinkDescription::Serial: return ::updateSerialLink(new SerialLink(), m_description);
    case LinkDescription::Udp: return ::updateUdpLink(new UdpLink(), m_description);
    case LinkDescription::Tcp: return ::updateTcpLink(new TcpLink(), m_description);
    default:
        return nullptr;
    }
}

void DescriptionLinkFactory::update(AbstractLink* link)
{
    if (m_description.isNull()) return;

    switch (m_description->type())
    {
    case LinkDescription::Serial:
    {
        if (SerialLink* serialLink = qobject_cast<SerialLink*>(link))
        {
            ::updateSerialLink(serialLink, m_description);
        }
        break;
    }
    case LinkDescription::Udp:
    {
       if (UdpLink* udpLink = qobject_cast<UdpLink*>(link))
       {
           ::updateUdpLink(udpLink, m_description);
       }
       break;
    }
    case LinkDescription::Tcp:
    {
       if (TcpLink* tcpLink = qobject_cast<TcpLink*>(link))
       {
           ::updateTcpLink(tcpLink, m_description);
       }
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
