#ifndef DTO_TRAITS_H
#define DTO_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace dto
{
    class Mission;
    class MissionItem;
    class MissionAssignment;
    class Command;
    class Vehicle;
    class VideoSource;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;
    using MissionAssignmentPtr  = QSharedPointer<MissionAssignment>;
    using CommandPtr = QSharedPointer<Command>;
    using VehiclePtr = QSharedPointer<Vehicle>;
    using VideoSourcePtr = QSharedPointer<VideoSource>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
    using MissionAssignmentPtrList = QList<MissionAssignmentPtr>;
    using CommandPtrList = QList<CommandPtr>;
    using VehiclePtrList = QList<VehiclePtr>;
    using VideoSourcePtrList = QList<VideoSourcePtr>;
}

#endif // DTO_TRAITS_H
