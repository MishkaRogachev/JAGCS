#ifndef LINK_DESCRIPTION_H
#define LINK_DESCRIPTION_H

#include "base_entity.h"

namespace data_source
{
    class LinkDescription : public BaseEntity
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

        QString device() const;
        void setDevice(const QString& device);

        int baudRate() const;
        void setBaudRate(int baudRate);

        bool isAutoConnect() const;
        void setAutoConnect(bool autoConnect);

    private:
        QString m_name;
        Type m_type = UnknownType;
        QString m_device;
        int m_baudRate = -1;
        bool m_autoConnect = false;

        Q_ENUM(Type)
    };
}

#endif // LINK_DESCRIPTION_H
