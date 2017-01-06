#ifndef MISSION_H
#define MISSION_H

// Qt
#include <QMap>

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
        int totalCount() const;

        MissionItem* item(int seq) const;
        QList<MissionItem*> items() const;
        int sequence(MissionItem* item) const;

    public slots:
        void setTotalCount(int totalCount);
        void setMissionItem(int seq, MissionItem* item);

        void addNewMissionItem();
        void removeMissionItem(MissionItem* item);

    signals:
        void totalCountChanged(int totalCount);
        void missionItemRemoved(MissionItem* item);
        void missionItemAdded(MissionItem* item);

    private:
        QMap<int, MissionItem*> m_items;
        int m_totalCount;
    };
}

#endif // MISSION_H
