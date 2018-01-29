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
    class Command;
    class Vehicle;
    class LinkDescription;
    class LinkStatistics;
    class VideoSource;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;
    using MissionAssignmentPtr  = QSharedPointer<MissionAssignment>;
    using CommandPtr = QSharedPointer<Command>;
    using VehiclePtr = QSharedPointer<Vehicle>;
    using LinkDescriptionPtr = QSharedPointer<LinkDescription>;
    using LinkStatisticsPtr = QSharedPointer<LinkStatistics>;
    using VideoSourcePtr = QSharedPointer<VideoSource>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
    using MissionAssignmentPtrList = QList<MissionAssignmentPtr>;
    using CommandPtrList = QList<CommandPtr>;
    using VehiclePtrList = QList<VehiclePtr>;
    using LinkDescriptionPtrList = QList<LinkDescriptionPtr>;
    using VideoSourcePtrList = QList<VideoSourcePtr>;
}

#endif // DAO_TRAITS_H
