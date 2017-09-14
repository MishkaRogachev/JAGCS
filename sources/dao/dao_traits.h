#ifndef DAO_TRAITS_H
#define DAO_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace dao
{
    class Mission;
    class MissionItem;
    class MissionAssignment;
    class Vehicle;
    class LinkDescription;
    class VideoSource;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;
    using MissionAssignmentPtr  = QSharedPointer<MissionAssignment>;
    using VehiclePtr = QSharedPointer<Vehicle>;
    using LinkDescriptionPtr = QSharedPointer<LinkDescription>;
    using VideoSourcePtr = QSharedPointer<VideoSource>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
    using MissionAssignmentPtrList = QList<MissionAssignmentPtr>;
    using VehiclePtrList = QList<VehiclePtr>;
    using LinkDescriptionPtrList = QList<LinkDescriptionPtr>;
    using VideoSourcePtrList = QList<VideoSourcePtr>;
}

#endif // DAO_TRAITS_H
