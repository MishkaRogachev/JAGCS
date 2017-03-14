#ifndef MISSION_ITEM_REPOSITORY_H
#define MISSION_ITEM_REPOSITORY_H

// Qt
#include <QList>

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

        MissionItem* createMissionItem();
        bool removeMissionItem(MissionItem* item);
        bool updateMissionItem(MissionItem* item);

        QList<MissionItem*> querty() const;

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // MISSION_ITEM_REPOSITORY_H
