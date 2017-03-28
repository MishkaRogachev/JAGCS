#ifndef DB_TRAITS_H
#define DB_TRAITS_H

// Qt
#include <QSharedPointer>
#include <QList>

namespace data_source
{
    class Mission;
    class MissionItem;
    class Vehicle;

    using MissionPtr = QSharedPointer<Mission>;
    using MissionItemPtr = QSharedPointer<MissionItem>;
    using VehiclePtr = QSharedPointer<Vehicle>;

    using MissionPtrList = QList<MissionPtr>;
    using MissionItemPtrList = QList<MissionItemPtr>;
    using VehiclePtrList = QList<VehiclePtr>;
}

#endif // DB_TRAITS_H
