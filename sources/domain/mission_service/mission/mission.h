#ifndef MISSION_H
#define MISSION_H

// Internal
#include "mission_item_factory.h"

namespace domain
{
    class Mission: public QObject
    {
        Q_OBJECT

    public:
        explicit Mission(QObject* parent = nullptr);

        int count() const;

        MissionItem* item(int seq) const;
        const QList<MissionItem*>& items() const;
        int sequence(MissionItem* item) const;

        MissionItem* requestItem(int seq, MissionItem::Command command);

    public slots:
        void setCount(int count);

        void addNewMissionItem();
        void removeMissionItem(MissionItem* item);

    signals:
        void missionItemRemoved(MissionItem* item);
        void missionItemAdded(MissionItem* item);

    private:
        MissionItemFactory m_itemFactory;
        QList<MissionItem*> m_items;
    };
}

#endif // MISSION_H
