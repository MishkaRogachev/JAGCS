#include "link_statistics.h"

using namespace dto;

int LinkStatistics::linkId() const
{
    return m_linkId;
}

void LinkStatistics::setLinkId(int linkId)
{
    m_linkId = linkId;
}

int LinkStatistics::timestamp() const
{
    return m_timestamp;
}

void LinkStatistics::setTimestamp(int timestamp)
{
    m_timestamp = timestamp;
}

int LinkStatistics::bytesSent() const
{
    return m_bytesSent;
}

void LinkStatistics::setBytesSent(int bytesSent)
{
    m_bytesSent = bytesSent;
}

int LinkStatistics::bytesRecv() const
{
    return m_bytesRecv;
}

void LinkStatistics::setBytesRecv(int bytesRecv)
{
    m_bytesRecv = bytesRecv;
}

int LinkStatistics::packetsRecv() const
{
    return m_packetsRecv;
}

void LinkStatistics::setPacketsRecv(int packetsRecv)
{
    m_packetsRecv = packetsRecv;
}

int LinkStatistics::packetDrops() const
{
    return m_packetDrops;
}

void LinkStatistics::setPacketDrops(int packetDrops)
{
    m_packetDrops = packetDrops;
}
