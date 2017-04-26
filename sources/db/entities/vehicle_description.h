#ifndef VEHICLE_DESCRIPTION_H
#define VEHICLE_DESCRIPTION_H

// Internal
#include "base_entity.h"

namespace db
{
    class VehicleDescription: public BaseEntity
    {
        Q_GADGET

        Q_PROPERTY(int mavId READ mavId WRITE setMavId)
        Q_PROPERTY(QString name READ name WRITE setName)

    public:
        VehicleDescription();
        ~VehicleDescription() override;

        int mavId() const;
        bool setMavId(int mavId);

        QString name() const;
        void setName(const QString& name);

    private:
        int m_mavId = 0;
        QString m_name;

        static QMap<VehicleDescription*, int> m_mavIds;
    };
}

#endif // VEHICLE_DESCRIPTION_H
