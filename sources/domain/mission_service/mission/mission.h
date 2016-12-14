#ifndef MISSION_H
#define MISSION_H

// Internal
#include "mission_item.h"

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

        MissionItem* requestItem(int seq);

    public slots:
        void setCount(int count);

        void addNewMissionItem();
        void removeMissionItem(MissionItem* item);

    signals:
        void missionItemRemoved(MissionItem* item);
        void missionItemAdded(MissionItem* item);

    private:
        QList<MissionItem*> m_missionItems;
    };
}

#endif // MISSION_H
