#ifndef VEHICLE_H
#define VEHICLE_H

// Internal
#include "base_entity.h"

namespace data_source
{
    class Vehicle: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(quint8 mavId READ mavId WRITE setMavId)
        Q_PROPERTY(QString name READ name WRITE setName)

    public:
        explicit Vehicle(IdentityMap* iMap);

        static QString tableName();

        quint8 mavId() const;
        void setMavId(quint8 mavId);

        QString name() const;
        void setName(const QString& name);

    private:
        quint8 m_mavId;
        QString m_name;
    };
}

#endif // VEHICLE_H
