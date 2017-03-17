#ifndef IDENTITY_MAP_H
#define IDENTITY_MAP_H

namespace data_source
{
    class Mission;
    class MissionItem;

    class IdentityMap
    {
    public:
        IdentityMap();
        ~IdentityMap();

        Mission* mission(int id);
        MissionItem* missionItem(int id);

    private:
        class Impl;
        Impl* const d;
    };
}

#endif // IDENTITY_MAP_H
