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

        int count() const;

    public slots:
        void setCount(unsigned count);

        void setMissionItem(unsigned seq, MissionItem* item);
        void removeMissionItem(unsigned seq);

    signals:
        void missionItemRemoved(unsigned seq);
        void missionItemAdded(unsigned seq);

    private:
        QMap<unsigned, MissionItem*> m_missionItems;
    };
}

#endif // MISSION_H
