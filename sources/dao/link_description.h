#ifndef LINK_DESCRIPTION_H
#define LINK_DESCRIPTION_H

#include "base_dao.h"

namespace dao
{
    class LinkDescription : public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(Type type READ type WRITE setType)
        Q_PROPERTY(int port READ port WRITE setPort)
        Q_PROPERTY(QString device READ device WRITE setDevice)
        Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate)
        Q_PROPERTY(bool autoConnect READ isAutoConnect WRITE setAutoConnect)

    public:
        enum Type: quint8
        {
            UnknownType = 0,
            Serial,
            Udp
        };

        QString name() const;
        void setName(const QString& name);

        Type type() const;
        void setType(Type type);

        int port() const;
        void setPort(int port);

        QString device() const;
        void setDevice(const QString& device);

        int baudRate() const;
        void setBaudRate(int baudRate);

        bool isAutoConnect() const;
        void setAutoConnect(bool autoConnect);

        bool isConnected() const;
        void setConnected(bool isConnected);

        int bytesSentSec() const;
        void setBytesSentSec(int bytesSentSec);

        int bytesRecvSec() const;
        void setBytesRecvSec(int bytesRecvSec);

        int packetsRecvSec() const;
        void setPacketsRecvSec(int packetsRecvSec);

        int packetDropsSec() const;
        void setPacketDropsSec(int packetDropsSec);

    private:
        QString m_name;
        Type m_type = UnknownType;
        int m_port = 0;
        QString m_device;
        int m_baudRate = -1;
        bool m_autoConnect = false;

        bool m_connected = false;
        int m_bytesSentSec = 0;
        int m_bytesRecvSec = 0;
        int m_packetsRecvSec = 0;
        int m_packetDropsSec = 0;

        Q_ENUM(Type)
    };
}

#endif // LINK_DESCRIPTION_H
