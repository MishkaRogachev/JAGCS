#ifndef DB_TRAITS_H
#define DB_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace db
{
    class Mission;
    class MissionItem;
    class MissionAssignment;
    class VehicleDescription;
    class LinkDescription;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;
    using MissionAssignmentPtr  = QSharedPointer<MissionAssignment>;
    using VehicleDescriptionPtr = QSharedPointer<VehicleDescription>; //TODO: rename to vehicle
    using LinkDescriptionPtr = QSharedPointer<LinkDescription>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
    using VehicleDescriptionPtrList = QList<VehicleDescriptionPtr>;
    using LinkDescriptionPtrList = QList<LinkDescriptionPtr>;
}

#endif // DB_TRAITS_H
