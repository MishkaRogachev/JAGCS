#ifndef ABSTRACT_VEHICLE_H
#define ABSTRACT_VEHICLE_H

// Qt
#include <QObject>

namespace domain
{
    class Mission;

    class AbstractVehicle: public QObject
    {
        Q_OBJECT

        Q_PROPERTY(uint8_t vehicleId READ vehicleId CONSTANT)
        Q_PROPERTY(int type READ type CONSTANT)

        Q_PROPERTY(int missionItems READ missionItems NOTIFY missionItemsChanged)
        Q_PROPERTY(int currentItem READ currentItem NOTIFY currentItemChanged)

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

        int missionItems() const;
        int currentItem() const;

    public slots:
        void assignMission(Mission* mission);
        void unassignMission();

    signals:
        void assignedMissionChanged(Mission* mission);
        void missionItemsChanged(int missionItems);
        void currentItemChanged(int currentItem);

        void commandReturn();
        void commandRestart();
        void commandStart(int missionItem);
        void commandJumpTo(int missionItem);

    protected:
        const uint8_t m_vehicleId;
        const int m_type;

        Mission* m_assignedMission;

        Q_ENUM(Type)
    };
}

#endif // ABSTRACT_VEHICLE_H
