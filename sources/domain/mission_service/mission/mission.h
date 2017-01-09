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
        ~Mission() override;

        int count() const;

        MissionItem* item(int seq) const;
        const QList<MissionItem*>& items() const;
        int sequence(MissionItem* item) const;

        MissionItem* take(int seq);

    public slots:
        void setCount(int count);
        void setMissionItem(int seq, MissionItem* item);

        void addNewMissionItem();
        void removeMissionItem(MissionItem* item);

        void exchange(int first, int last);

    signals:
        void missionItemsChanged(const QList<MissionItem*>& items);

    private:
        QList<MissionItem*> m_items;
    };
}

#endif // MISSION_H
