#ifndef MISSION_ITEM_REPOSITORY_H
#define MISSION_ITEM_REPOSITORY_H

// Qt
#include <QList>

// Internal
#include "command.h"

namespace data_source
{
    class MissionItem;

    class MissionItemRepository
    {
    public:
        MissionItemRepository();
        ~MissionItemRepository();

        bool createRepository();
        bool dropRepository();

        MissionItem* createMissionItem(); // TODO: invalid item instead null
        MissionItem* readMissionItem(int id);
        bool updateMissionItem(MissionItem* item);
        bool deleteMissionItem(MissionItem* item);

        QList<MissionItem*> querty() const;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_ITEM_REPOSITORY_H
