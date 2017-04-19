#ifndef DB_TRAITS_H
#define DB_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace data_source
{
    class Mission;
    class MissionItem;
    class VehicleDescription;
    class LinkDescription;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;
    using VehicleDescriptionPtr = QSharedPointer<VehicleDescription>;
    using LinkDescriptionPtr = QSharedPointer<LinkDescription>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
    using VehicleDescriptionPtrList = QList<VehicleDescriptionPtr>;
    using LinkDescriptionPtrList = QList<LinkDescriptionPtr>;
}

#endif // DB_TRAITS_H
