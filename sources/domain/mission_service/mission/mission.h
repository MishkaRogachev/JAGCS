#ifndef MISSION_H
#define MISSION_H

// Internal
#include "mission_item.h"

namespace domain
{
    class MissionVehicle;
    class AbstractVehicle;

    class Mission: public QObject
    {
        Q_OBJECT

    public:
        explicit Mission(QObject* parent = nullptr);
        ~Mission() override;

        int count() const;

        MissionItem* item(int seq) const;
        const QList<MissionItem*>& items() const;
        int sequence(MissionItem* item) const;

        MissionItem* take(int seq);

        MissionVehicle* assignment() const;
        AbstractVehicle* assignedVehicle() const;

    public slots:
        void setCount(int count);
        void setMissionItem(int seq, MissionItem* item);

        void addNewMissionItem();
        void removeMissionItem(MissionItem* item);

        void exchange(int first, int last);

        void unassignVehicle();
        void assignVehicle(AbstractVehicle* vehicle);

    signals:
        void missionItemsChanged(const QList<MissionItem*>& items);

        void assigned(AbstractVehicle* vehicle);
        void unassigned();

    private:
        QList<MissionItem*> m_items;
        MissionVehicle* const m_assignment;
    };
}

#endif // MISSION_H
