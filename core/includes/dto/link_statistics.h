#ifndef LINK_STATISTICS_H
#define LINK_STATISTICS_H

// Internal
#include "base_dto.h"

namespace dto
{
// TODO: remove link statistics dao
    class LinkStatistics: public BaseDto
    {
        Q_GADGET

        Q_PROPERTY(int linkId READ linkId WRITE setLinkId)
        Q_PROPERTY(int timestamp READ timestamp WRITE setTimestamp)
        Q_PROPERTY(int bytesSent READ bytesSent WRITE setBytesSent)
        Q_PROPERTY(int bytesRecv READ bytesRecv WRITE setBytesRecv)
        Q_PROPERTY(int packetsRecv READ packetsRecv WRITE setPacketsRecv)
        Q_PROPERTY(int packetDrops READ packetDrops WRITE setPacketDrops)

    public:
        int linkId() const;
        void setLinkId(int linkId);

        int timestamp() const;
        void setTimestamp(int timestamp);

        int bytesSent() const;
        void setBytesSent(int bytesSent);

        int bytesRecv() const;
        void setBytesRecv(int bytesRecv);

        int packetsRecv() const;
        void setPacketsRecv(int packetsRecv);

        int packetDrops() const;
        void setPacketDrops(int packetDrops);

    private:
        int m_linkId = 0;
        int m_timestamp = 0;
        int m_bytesSent = 0;
        int m_bytesRecv = 0;
        int m_packetsRecv = 0;
        int m_packetDrops = 0;
    };
}

#endif // LINK_STATISTICS_H
