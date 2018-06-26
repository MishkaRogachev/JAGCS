#include "description_link_factory.h"

// Internal
#include "link_description.h"

#include "serial_link.h"
#include "udp_link.h"
#include "tcp_link.h"
#include "bluetooth_link.h"

using namespace dto;
using namespace comm;

namespace
{
    SerialLink* updateSerial(SerialLink* serialLink, const LinkDescriptionPtr& description)
    {
        serialLink->setDevice(description->parameter(dto::LinkDescription::Device).toString());
        serialLink->setBaudRate(description->parameter(dto::LinkDescription::BaudRate).toInt());

        return serialLink;
    }

    UdpLink* updateUdp(UdpLink* udpLink, const LinkDescriptionPtr& description)
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

    TcpLink* updateTcp(TcpLink* tcpLink, const LinkDescriptionPtr& description)
    {
        Endpoint endpoint;

        endpoint.setAddress(QHostAddress(description->parameter(LinkDescription::Address).toString()));
        endpoint.setPort(description->parameter(dto::LinkDescription::Port).toInt());

        tcpLink->setEndpoint(endpoint);

        return tcpLink;
    }

    BluetoothLink* updateBluetooth(BluetoothLink* link, const LinkDescriptionPtr& description)
    {
        link->setAddress(description->parameter(LinkDescription::Address).toString());

        return link;
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
    case LinkDescription::Serial: return ::updateSerial(new SerialLink(), m_description);
    case LinkDescription::Udp: return ::updateUdp(new UdpLink(), m_description);
    case LinkDescription::Tcp: return ::updateTcp(new TcpLink(), m_description);
    case LinkDescription::Bluetooth: return ::updateBluetooth(new BluetoothLink(), m_description);
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
            ::updateSerial(serialLink, m_description);
        }
        break;
    }
    case LinkDescription::Udp:
    {
       if (UdpLink* udpLink = qobject_cast<UdpLink*>(link))
       {
           ::updateUdp(udpLink, m_description);
       }
       break;
    }
    case LinkDescription::Tcp:
    {
       if (TcpLink* tcpLink = qobject_cast<TcpLink*>(link))
       {
           ::updateTcp(tcpLink, m_description);
       }
       break;
    }
    case LinkDescription::Bluetooth:
    {
       if (BluetoothLink* bluetoothLink = qobject_cast<BluetoothLink*>(link))
       {
           ::updateBluetooth(bluetoothLink, m_description);
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
