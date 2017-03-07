#ifndef MISSION_H
#define MISSION_H

// Internal
#include "abstract_mission_item.h"

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
        int currentIndex() const;

        AbstractMissionItem* item(int seq) const;
        AbstractMissionItem* currentItem() const;
        const QList<AbstractMissionItem*>& items() const;

        int sequence(AbstractMissionItem* item) const;

        AbstractMissionItem* take(int seq);

        MissionVehicle* assignment() const;
        AbstractVehicle* assignedVehicle() const;

    public slots:
        void setCount(int count);
        void setCurrentIndex(int index);
        void setMissionItem(int seq, AbstractMissionItem* item);

        void addNewMissionItem();
        void removeMissionItem(AbstractMissionItem* item);

        void exchange(int first, int last);

        void unassignVehicle();
        void assignVehicle(AbstractVehicle* vehicle);

    signals:
        void missionItemsChanged(const QList<AbstractMissionItem*>& items);
        void missionItemDataChanged(AbstractMissionItem* item);
        void currentIndexChanged(int index);

        void assigned(AbstractVehicle* vehicle);
        void unassigned();

    private slots:
        void onMissionItemDataChanged();

    private:
        QList<AbstractMissionItem*> m_items;
        MissionVehicle* const m_assignment;
        int m_currentIndex;
    };
}

#endif // MISSION_H
