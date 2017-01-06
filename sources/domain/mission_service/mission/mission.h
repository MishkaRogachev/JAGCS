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

        MissionItem* item(int seq) const;
        QList<MissionItem*> items() const;
        int sequence(MissionItem* item) const;

        MissionItem* take(int seq);

    public slots:
        void setMissionItem(int seq, MissionItem* item);

        void addNewMissionItem();
        void deleteMissionItem(MissionItem* item);

        void exchange(int first, int last);

    signals:
        void missionItemRemoved(MissionItem* item);
        void missionItemAdded(MissionItem* item);

    private:
        QMap<int, MissionItem*> m_items;
    };
}

#endif // MISSION_H
