#ifndef IDENTITY_TRAITS_H
#define IDENTITY_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace data_source
{
    class Mission;
    class MissionItem;
    class Vehicle;
    class MissionAssignment;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;
    using VehiclePtr = QSharedPointer<Vehicle>;
    using MissionAssignmentPtr = QSharedPointer<MissionAssignment>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
    using VehiclePtrList = QList<VehiclePtr>;
}

#endif // IDENTITY_TRAITS_H
