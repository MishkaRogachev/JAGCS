#ifndef VEHICLE_H
#define VEHICLE_H

// Internal
#include "base_dao.h"

namespace dao
{
    class Vehicle: public BaseDao
    {
        Q_GADGET

        Q_PROPERTY(int mavId READ mavId WRITE setMavId)
        Q_PROPERTY(QString name READ name WRITE setName)
        Q_PROPERTY(Type type READ type WRITE setType)

    public:
        enum Type: quint8
        {
            UnknownType = 0,
            Auto = 1,

            FixedWing = 10,
            FlyingWing = 11,

            Quadcopter = 20,
            Tricopter = 21,
            Hexcopter = 22,
            Octocopter = 23,

            Helicopter = 30,
            Coaxial = 31,

            Vtol = 40,

            Airship = 60,
            Kite = 61,
            Ornithopter = 62
        };

        Vehicle();
        ~Vehicle() override;

        int mavId() const;
        bool setMavId(int mavId);

        QString name() const;
        void setName(const QString& name);

        Type type() const;
        void setType(Type type);

        bool isOnline() const;
        void setOnline(bool isOnline);

    private:
        int m_mavId = 0;
        QString m_name;
        Type m_type = Auto;

        static QMap<Vehicle*, int> m_mavIds;
        bool m_online;

        Q_ENUM(Type)
    };
}

#endif // VEHICLE_H
