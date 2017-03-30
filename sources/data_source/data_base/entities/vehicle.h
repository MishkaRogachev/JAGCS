#ifndef VEHICLE_H
#define VEHICLE_H

// Internal
#include "base_entity.h"

namespace data_source
{
    class Vehicle: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(int mavId READ mavId WRITE setMavId)
        Q_PROPERTY(QString name READ name WRITE setName)

    public:
        Vehicle();

        int mavId() const;
        void setMavId(int mavId);

        QString name() const;
        void setName(const QString& name);

    private:
        int m_mavId;
        QString m_name;
    };
}

#endif // VEHICLE_H
