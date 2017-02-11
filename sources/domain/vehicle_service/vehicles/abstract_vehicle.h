#ifndef ABSTRACT_VEHICLE_H
#define ABSTRACT_VEHICLE_H

#include <QObject>

namespace domain
{
    class Mission;

    class AbstractVehicle: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(uint8_t vehicleId READ vehicleId CONSTANT)
        Q_PROPERTY(int type READ type WRITE setType NOTIFY typeChanged)

    public:
        enum Type
        {
            UnknownType = 0
        };

        AbstractVehicle(uint8_t vehicleId, int type, QObject* parent = nullptr);
        ~AbstractVehicle() override;

        uint8_t vehicleId() const;

        int type() const;

        Mission* assignedMission() const;

    public slots:
        void setType(int type);

        void assignMission(Mission* mission);
        void unassignMission();

    signals:
        void typeChanged(int type);

        void assignedMissionChanged(Mission* mission);

    private:
        uint8_t m_vehicleId;
        int m_type;

        Mission* m_assignedMission;
    };
}

#endif // ABSTRACT_VEHICLE_H
