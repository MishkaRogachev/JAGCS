#include "link_description.h"

// Internal
#include "settings_provider.h"

using namespace dao;

LinkDescription::LinkDescription():
    BaseDao(),
    m_statistcsCount(settings::Provider::value(settings::communication::statisticsCount).toUInt())
{}

QString LinkDescription::name() const
{
    return m_name;
}

void LinkDescription::setName(const QString& name)
{
    m_name = name;
}

LinkDescription::Type LinkDescription::type() const
{
    return m_type;
}

void LinkDescription::setType(LinkDescription::Type type)
{
    m_type = type;
}

int LinkDescription::port() const
{
    return m_port;
}

void LinkDescription::setPort(int port)
{
    m_port = port;
}

QString LinkDescription::device() const
{
    return m_device;
}

void LinkDescription::setDevice(const QString& device)
{
    m_device = device;
}

int LinkDescription::baudRate() const
{
    return m_baudRate;
}

void LinkDescription::setBaudRate(int baudRate)
{
    m_baudRate = baudRate;
}

bool LinkDescription::isAutoConnect() const
{
    return m_autoConnect;
}

void LinkDescription::setAutoConnect(bool autoConnect)
{
    m_autoConnect = autoConnect;
}

bool LinkDescription::isConnected() const
{
    return m_connected;
}

void LinkDescription::setConnected(bool connected)
{
    m_connected = connected;
}

const QList<int>& LinkDescription::bytesSent() const
{
    return m_bytesSent;
}

void LinkDescription::addBytesSent(int bytesSent)
{
    m_bytesSent.append(bytesSent);
    while (m_bytesSent.count() > m_statistcsCount) m_bytesSent.removeFirst();
}

const QList<int>& LinkDescription::bytesRecv() const
{
    return m_bytesRecv;
}

void LinkDescription::addBytesRecv(int bytesRecv)
{
    m_bytesRecv.append(bytesRecv);
    while (m_bytesRecv.count() > m_statistcsCount) m_bytesRecv.removeFirst();
}

const QList<int>& LinkDescription::packetsRecv() const
{
    return m_packetsRecv;
}

void LinkDescription::addPacketsRecv(int packetsRecv)
{
    m_packetsRecv.append(packetsRecv);
    while (m_packetsRecv.count() > m_statistcsCount) m_packetsRecv.removeFirst();
}

const QList<int>& LinkDescription::packetDrops() const
{
    return m_packetDrops;
}

void LinkDescription::addPacketDrops(int packetDrops)
{
    m_packetDrops.append(packetDrops);
    while (m_packetDrops.count() > m_statistcsCount) m_packetDrops.removeFirst();
}

LinkDescription::Protocol LinkDescription::protocol() const
{
    return m_protocol;
}

void LinkDescription::setProtocol(Protocol protocol)
{
    m_protocol = protocol;
}
