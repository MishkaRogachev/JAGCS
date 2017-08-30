#ifndef LINK_DESCRIPTION_H
#define LINK_DESCRIPTION_H

#include "base_dao.h"

namespace dao
{
    class LinkDescription: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(Type type READ type WRITE setType)
        Q_PROPERTY(int port READ port WRITE setPort)
        Q_PROPERTY(QString device READ device WRITE setDevice)
        Q_PROPERTY(int baudRate READ baudRate WRITE setBaudRate)
        Q_PROPERTY(bool autoConnect READ isAutoConnect WRITE setAutoConnect)

    public:
        LinkDescription();

        enum Type: quint8
        {
            UnknownType = 0,
            Serial,
            Udp
        };

        enum Protocol: quint8
        {
            UnknownProtocol = 0,
            MavLink1,
            MavLink2
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

        const QList<int>& bytesSent() const;
        void addBytesSent(int bytesSent);

        const QList<int>& bytesRecv() const;
        void addBytesRecv(int bytesRecv);

        const QList<int>& packetsRecv() const;
        void addPacketsRecv(int packetsRecv);

        const QList<int>& packetDrops() const;
        void addPacketDrops(int packetDrops);

        Protocol protocol() const;
        void setProtocol(Protocol protocol);

    private:
        QString m_name;
        Type m_type = UnknownType;
        int m_port = 0;
        QString m_device;
        int m_baudRate = -1;
        bool m_autoConnect = false;

        Protocol m_protocol = UnknownProtocol;
        bool m_connected = false;

        int m_statistcsCount;
        QList<int> m_bytesSent;
        QList<int> m_bytesRecv;
        QList<int> m_packetsRecv;
        QList<int> m_packetDrops;

        Q_ENUM(Type)
        Q_ENUM(Protocol)
    };
}

#endif // LINK_DESCRIPTION_H
